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
use Drupal\Core\Entity\Query\QueryInterface;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Session\AccountSwitcherInterface;
use Drupal\scheduled_updates\Plugin\BaseUpdateRunner;
use Drupal\scheduled_updates\RevisionUtils;
use Drupal\workbench_moderation\ModerationInformationInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * The default Update Runner.
 *
 * @UpdateRunner(
 *   id = "workbench_moderation",
 *   label = @Translation("Workbench Moderation Update Runner"),
 *   description = @Translation("Runs updates for moderation content.")
 * )
 */
class ModerationUpdateRunner extends BaseUpdateRunner{

  /**
   * @var \Drupal\workbench_moderation\ModerationInformationInterface
   */
  protected $moderationInfo;

  public function __construct(array $configuration, $plugin_id, $plugin_definition, EntityFieldManagerInterface $fieldManager, EntityTypeManagerInterface $entityTypeManager, RevisionUtils $revisionUtils, AccountSwitcherInterface $accountSwitcher, ModerationInformationInterface $moderationInfo) {
    parent::__construct($configuration, $plugin_id, $plugin_definition, $fieldManager, $entityTypeManager, $revisionUtils, $accountSwitcher);
    $this->moderationInfo = $moderationInfo;
  }

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



  protected function getReferencingUpdates() {
    return [];
  }



  public function getReferencedUpdates() {
    $updates = [];
    /** @var String[] $fields */
    if ($field_ids = $this->getReferencingFieldIds()) {

      //$query = $entity_storage->getQuery('OR');
      $entity_ids = [];

      $entity_storage = $this->entityTypeManager->getStorage($this->updateEntityType());
      foreach ($field_ids as $field_id) {

        $query = $entity_storage->getQuery('AND');
        $this->addActiveUpdateConditions($query, "$field_id.entity.");
        $query->allRevisions();
        $entity_ids += $query->execute();
      }
      /** @var ContentEntityInterface[] $entities */
      //$entities = $entity_storage->loadMultiple(array_unique($entity_ids));
      $revisions_to_update = [];
      $entity_ids = array_unique($entity_ids);
      foreach ($entity_ids as $entity_id) {
        $revisions_to_update[$entity_id] = $this->moderationInfo->getLatestRevision($this->updateEntityType(), $entity_id);
      }
      /** @var ContentEntityInterface $revision */
      foreach ($revisions_to_update as $entity_id => $revision) {
        /** @var  $entity_update_ids - all update ids for this entity for our fields. */
        $entity_update_ids = [];
        /** @var  $field_update_ids - update ids keyed by field_id. */
        $field_update_ids = [];
        foreach ($field_ids as $field_id) {
          // Store with field id.
          $field_update_ids[$field_id] = $this->getEntityReferenceTargetIds($revision, $field_id);
          // Add to all for entity.
          $entity_update_ids += $field_update_ids[$field_id];
        }
        // For all entity updates return only those ready to run.
        $ready_update_ids = $this->getReadyUpdates($entity_update_ids);
        // Loop through updates attached to fields.
        foreach ($field_update_ids as $field_id => $update_ids) {
          // For updates attached to field get only those ready to run.
          $field_ready_update_ids = array_intersect($update_ids, $ready_update_ids);
          foreach ($field_ready_update_ids as $field_ready_update_id) {
            $updates[] = [
              'update_id' => $field_ready_update_id,
              'entity_ids' => [$revision->id()],
              //'revision_id' => $revision->getRevisionId(),
              'field_id' => $field_id,
              'entity_type' => $this->updateEntityType(),
            ];
          }
        }
      }
    }
    debug($updates, $this->scheduled_update_type->id());
    return $updates;
  }

  /**
   * {@inheritdoc}
   */
  protected function loadEntitiesToUpdate($entity_ids) {
    $revisions = [];
    foreach ($entity_ids as $entity_id) {
      $revisions[$entity_id] = $this->moderationInfo->getLatestRevision($this->updateEntityType(), $entity_id);
    }
    return $revisions;
  }


}
