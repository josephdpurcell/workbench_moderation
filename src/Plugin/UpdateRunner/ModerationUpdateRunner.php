<?php
/**
 * @file
 * Contains
 * \Drupal\workbench_moderation\Plugin\UpdateRunner\ModerationUpdateRunner.
 */


namespace Drupal\workbench_moderation\Plugin\UpdateRunner;


use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\Core\Entity\EntityFieldManagerInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Session\AccountSwitcherInterface;
use Drupal\scheduled_updates\Plugin\BaseUpdateRunner;
use Drupal\scheduled_updates\Plugin\EntityMonitorUpdateRunnerInterface;
use Drupal\scheduled_updates\RevisionUtils;
use Drupal\scheduled_updates\ScheduledUpdateInterface;
use Drupal\workbench_moderation\ModerationInformationInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * The Workbench Moderation Update Runner.
 *
 * Works with Scheduled Updates module: https://www.drupal.org/project/scheduled_updates
 *
 *
 * @UpdateRunner(
 *   id = "workbench_moderation",
 *   label = @Translation("Workbench Moderation Update Runner"),
 *   description = @Translation("Runs updates for moderation content.")
 * )
 */
class ModerationUpdateRunner extends BaseUpdateRunner implements EntityMonitorUpdateRunnerInterface{

  /**
   * @var \Drupal\workbench_moderation\ModerationInformationInterface
   */
  protected $moderationInfo;

  /**
   * ModerationUpdateRunner constructor.
   *
   * @param array $configuration
   * @param string $plugin_id
   * @param mixed $plugin_definition
   * @param \Drupal\Core\Entity\EntityFieldManagerInterface $fieldManager
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entityTypeManager
   * @param \Drupal\scheduled_updates\RevisionUtils $revisionUtils
   * @param \Drupal\Core\Session\AccountSwitcherInterface $accountSwitcher
   * @param \Drupal\workbench_moderation\ModerationInformationInterface $moderationInfo
   */
  public function __construct(array $configuration, $plugin_id, $plugin_definition, EntityFieldManagerInterface $fieldManager, EntityTypeManagerInterface $entityTypeManager, RevisionUtils $revisionUtils, AccountSwitcherInterface $accountSwitcher, ModerationInformationInterface $moderationInfo) {
    parent::__construct($configuration, $plugin_id, $plugin_definition, $fieldManager, $entityTypeManager, $revisionUtils, $accountSwitcher);
    $this->moderationInfo = $moderationInfo;
  }

  /**
   * @param \Symfony\Component\DependencyInjection\ContainerInterface $container
   * @param array $configuration
   * @param string $plugin_id
   * @param mixed $plugin_definition
   *
   * @return static
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('entity_field.manager'),
      $container->get('entity_type.manager'),
      $container->get('scheduled_updates.type_info'),
      $container->get('account_switcher'),
      $container->get('workbench_moderation.moderation_information')
    );
  }

  /**
   * {@inheritdoc}
   */
  protected function getReferencingUpdates() {
    // @todo Logic for independent updates
    return [];
  }

  /**
   * {@inheritdoc}
   */
  protected function getEntityIdsReferencingReadyUpdates() {
    $entity_ids = [];
    if ($field_ids = $this->getReferencingFieldIds()) {
      $entity_storage = $this->entityTypeManager->getStorage($this->updateEntityType());
      $all_ready_update_ids = $this->getReadyUpdateIds();
      foreach ($field_ids as $field_id) {

        $query = $entity_storage->getQuery('AND');
        $query->condition("$field_id.target_id", $all_ready_update_ids, 'IN');
        $query->allRevisions();
        $entity_ids += $query->execute();
      }
    }
    return $entity_ids;
  }

  /**
   * {@inheritdoc}
   */
  protected function loadEntitiesToUpdate($entity_ids) {
    $revision_ids = array_keys($entity_ids);
    $entity_ids = array_unique($entity_ids);
    $revisions = [];
    foreach ($entity_ids as $entity_id) {
      $latest_revision = $this->moderationInfo->getLatestRevision($this->updateEntityType(), $entity_id);
      // Check the latest revision was in the revisions sent to this function.
      if (in_array($latest_revision->getRevisionId(), $revision_ids)) {
        $revisions[$entity_id] = $latest_revision;
      }
    }
    return $revisions;
  }

  /**
   * {@inheritdoc}
   */
  public function onEntityUpdate(ContentEntityInterface $entity) {
    $this->deactivateUpdates($entity);
    $this->reactivateUpdates($entity);
  }


  /**
   * Get all update ids for this connected Update type.
   *
   * @todo Should results be cached per entity_id and revision_id to avoiding loading updates.
   *
   * @param \Drupal\Core\Entity\ContentEntityInterface $entity
   *
   * @return array
   */
  protected function getUpdateIdsOnEntity(ContentEntityInterface $entity, $include_inactive = FALSE) {
    $field_ids = $this->getReferencingFieldIds();
    $update_ids = [];
    foreach ($field_ids as $field_id) {
      $field_update_ids = $this->getEntityReferenceTargetIds($entity, $field_id);
      // This field could reference other update bundles
      // remove any that aren't of the attached scheduled update type.
      foreach ($field_update_ids as $field_update_id) {
        $update = $this->entityTypeManager->getStorage('scheduled_update')->load($field_update_id);
        if ($update->bundle() == $this->scheduled_update_type->id()) {
          if (!$include_inactive) {
            if ($update->status->value == ScheduledUpdateInterface::STATUS_INACTIVE) {
              continue;
            }
          }
          $update_ids[$field_update_id] = $field_update_id;
        }
      }
    }
    return $update_ids;
  }

  /**
   * Get all previous revisions that have updates of the attached type.
   *
   * This function would be easier and more performant if this core issue with Entity Query was fixed:
   *  https://www.drupal.org/node/2649268
   *  Without this fix can't filter query on type of update and whether they are active.
   *  So therefore all previous revisions have to be loaded.
   *
   * @todo Help get that core issue fixed or rewrite this function query table fields directly.
   *
   * @param \Drupal\Core\Entity\ContentEntityInterface $entity
   */
  protected function getPreviousRevisionsWithUpdates(ContentEntityInterface $entity) {
    /** @var ContentEntityInterface[] $revisions */
    $revisions = [];
    $type = $entity->getEntityType();
    $query = $this->entityTypeManager->getStorage($entity->getEntityTypeId())->getQuery();
    $query->allRevisions()
      ->condition($type->getKey('id'), $entity->id())
      ->condition($type->getKey('revision'), $entity->getRevisionId(), '<')
      ->sort($type->getKey('revision'), 'DESC');
    if ($revision_ids = $query->execute()) {
      $revision_ids = array_keys($revision_ids);
      $storage = $this->entityTypeManager->getStorage($entity->getEntityTypeId());
      foreach ($revision_ids as $revision_id) {
        /** @var ContentEntityInterface $revision */
        $revision = $storage->loadRevision($revision_id);
        if ($update_ids = $this->getUpdateIdsOnEntity($revision)) {
          $revisions[$revision_id] = $revision;
        }
      }
    }
    return $revisions;
  }

  /**
   * Deactivate any Scheduled Updates that are previous revision but not on current.
   *
   * @param \Drupal\Core\Entity\ContentEntityInterface $entity
   */
  protected function deactivateUpdates(ContentEntityInterface $entity) {
    $current_update_ids = $this->getUpdateIdsOnEntity($entity);
    // Loop through all previous revisions and deactive updates not on current revision.
    $revisions = $this->getPreviousRevisionsWithUpdates($entity);
    if (empty($revisions)) {
      return;
    }
    $all_revisions_update_ids = [];
    foreach ($revisions as $revision) {
      // array_merge so so elements with same key are not replaced.
      $all_revisions_update_ids = array_merge($all_revisions_update_ids,$this->getUpdateIdsOnEntity($revision));
    }
    $all_revisions_update_ids = array_unique($all_revisions_update_ids);
    $updates_ids_not_on_current = array_diff($all_revisions_update_ids, $current_update_ids);
    if ($updates_ids_not_on_current) {
      $storage = $this->entityTypeManager->getStorage('scheduled_update');
      foreach ($updates_ids_not_on_current as $update_id) {
        /** @var ScheduledUpdateInterface $update */
        $update = $storage->load($update_id);
        $update->status = ScheduledUpdateInterface::STATUS_INACTIVE;
        $update->save();
      }
    }
  }
  
  /**
   * Reactive any updates that are on this entity that have been deactived previously.
   *
   * @see ::deactivateUpdates()
   *
   * @param \Drupal\Core\Entity\ContentEntityInterface $entity
   */
  protected function reactivateUpdates(ContentEntityInterface $entity) {
    $update_ids = $this->getUpdateIdsOnEntity($entity);
    $storage = $this->entityTypeManager->getStorage('scheduled_update');
    $query = $storage->getQuery();
    $query->condition('status', [ScheduledUpdateInterface::STATUS_UNRUN, ScheduledUpdateInterface::STATUS_REQUEUED], 'NOT IN');
    $query->condition($this->entityTypeManager->getDefinition('scheduled_update')->getKey('id'), $update_ids, 'IN');
    $non_active_update_ids = $query->execute();
    $non_active_updates = $storage->loadMultiple($non_active_update_ids);
    foreach ($non_active_updates as $non_active_update) {
      $non_active_update->status = ScheduledUpdateInterface::STATUS_UNRUN;
    }
  }
}
