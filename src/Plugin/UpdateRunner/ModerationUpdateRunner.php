<?php
/**
 * @file
 * Contains
 * \Drupal\workbench_moderation\Plugin\UpdateRunner\ModerationUpdateRunner.
 */


namespace Drupal\workbench_moderation\Plugin\UpdateRunner;

use Drupal\Core\Entity\EntityFieldManagerInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Session\AccountSwitcherInterface;
use Drupal\scheduled_updates\Plugin\UpdateRunner\EmbeddedUpdateRunner;
use Drupal\scheduled_updates\UpdateUtils;
use Drupal\scheduled_updates\ScheduledUpdateTypeInterface;
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
 *   description = @Translation("Runs updates for moderation content."),
 *   update_types = {"embedded"}
 * )
 */
class ModerationUpdateRunner extends EmbeddedUpdateRunner {

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
   * @param \Drupal\scheduled_updates\UpdateUtils $updateUtils
   * @param \Drupal\Core\Session\AccountSwitcherInterface $accountSwitcher
   * @param \Drupal\workbench_moderation\ModerationInformationInterface $moderationInfo
   */
  public function __construct(array $configuration, $plugin_id, $plugin_definition, EntityFieldManagerInterface $fieldManager, EntityTypeManagerInterface $entityTypeManager, UpdateUtils $updateUtils, AccountSwitcherInterface $accountSwitcher, ModerationInformationInterface $moderationInfo) {
    parent::__construct($configuration, $plugin_id, $plugin_definition, $fieldManager, $entityTypeManager, $updateUtils, $accountSwitcher);
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
  protected function getEntityIdsReferencingReadyUpdates() {
    $entity_ids = [];
    if ($field_ids = $this->getReferencingFieldIds()) {
      $entity_storage = $this->entityTypeManager->getStorage($this->updateEntityType());
      $all_ready_update_ids = $this->getReadyUpdateIds();
      if ($all_ready_update_ids) {
        foreach ($field_ids as $field_id) {
          $query = $entity_storage->getQuery('AND');
          $query->condition("$field_id.target_id", $all_ready_update_ids, 'IN');
          $query->allRevisions();
          $entity_ids += $query->execute();
        }
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
  public function validateConfigurationForm(array &$form, FormStateInterface $form_state) {
    parent::validateConfigurationForm($form, $form_state);
    /** @var ScheduledUpdateTypeInterface $scheduled_update_type */
    $scheduled_update_type = $form_state->get('scheduled_update_type');
    // Check if entity type to be updated supports revisions.
    if (!$this->updateUtils->supportsRevisionUpdates($scheduled_update_type)) {
      // @todo Check if any bundles in update entity type is moderated
      $form_state->setError(
        $form['update_entity_type'],
        $this->t('The workbench moderation runner cannot be used with an entity type that does not support revisions.'
        )
      );
    }

  }


}
