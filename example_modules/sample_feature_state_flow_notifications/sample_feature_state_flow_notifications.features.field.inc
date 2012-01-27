<?php
/**
 * @file
 * sample_feature_state_flow_notifications.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function sample_feature_state_flow_notifications_field_default_fields() {
  $fields = array();

  // Exported field: 'state_flow_history_entity-state_flow_history_entity-field_stateflow_next_editor'
  $fields['state_flow_history_entity-state_flow_history_entity-field_stateflow_next_editor'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_stateflow_next_editor',
      'foreign keys' => array(
        'uid' => array(
          'columns' => array(
            'uid' => 'uid',
          ),
          'table' => 'users',
        ),
      ),
      'indexes' => array(
        'uid' => array(
          0 => 'uid',
        ),
      ),
      'module' => 'user_reference',
      'settings' => array(
        'referenceable_roles' => array(
          2 => '2',
          3 => 0,
        ),
        'referenceable_status' => array(
          0 => 0,
          1 => '1',
        ),
        'view' => array(
          'args' => array(),
          'display_name' => '',
          'view_name' => '',
        ),
      ),
      'translatable' => '0',
      'type' => 'user_reference',
    ),
    'field_instance' => array(
      'bundle' => 'state_flow_history_entity',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => 'Enter the username of the next editor who should should review this node. That person will receive an email notification.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'user_reference',
          'settings' => array(),
          'type' => 'user_reference_default',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'state_flow_history_entity',
      'field_name' => 'field_stateflow_next_editor',
      'label' => 'Next Editor',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'user_reference',
        'settings' => array(
          'autocomplete_match' => 'contains',
          'autocomplete_path' => 'user_reference/autocomplete',
          'size' => '60',
        ),
        'type' => 'user_reference_autocomplete',
        'weight' => '4',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Enter the username of the next editor who should should review this node. That person will receive an email notification.');
  t('Next Editor');

  return $fields;
}
