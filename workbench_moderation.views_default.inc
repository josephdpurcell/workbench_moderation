<?php

/**
 * Implements hook_views_default_views().
 */
function workbench_moderation_views_default_views() {
  $module = 'workbench_moderation';
  $directory = 'views';
  $extension = 'view.inc';
  $name = 'view';

  // From workbench_load_all_exports().
  $return = array();
  // Find all the files in the directory with the correct extension.
  $files = file_scan_directory(drupal_get_path('module', $module) . "/$directory", "/.$extension/");
  foreach ($files as $path => $file) {
    require $path;
    if (isset($$name)) {
      $return[$$name->name] = $$name;
    }
  }

  return $return;
}











/**
 * @file
 *  Content moderation views integration for Workbench.
 */

/**
 * Implements hook_views_data().
 */
function workbench_moderation_views_data_alter(&$data) {
dpm("in views_data_alter");
//dpm($data);
  $data['state_flow_states']['state'] = array(
    'title' => t('Current State from WBM'),
    'help' => t('---'),
    'field' => array(
      'handler' => 'views_handler_field_string',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'workbench_moderation_handler_filter_state',
      'label' => t('Current State Filter'),
      'type' => 'select',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // i don't think we can rely on workbench_workflow_states...states code be in code
  // same goes for workbench_workflow_events
  $data['workbench_moderation_states']['table']['group'] = t('Workbench Moderation');
  $data['workbench_moderation_states']['table']['join'] = array(
    // Add a join for labeling the 'state' and 'from_state'
    // arguments on workbench_moderation_node_history.
    'state_flow_states' => array(
      'left_field' => 'state',
      'field' => 'name',
    ),
    // @ todo - do we need these joins too?
/*    'node' => array(
      'left_table' => 'state_flow_states',
      'left_field' => 'state',
      'field' => 'name',
    ),
    'node_revision' => array(
      'left_table' => 'state_flow_history',
      'left_field' => 'state',
      'field' => 'name',
    ),*/
  );
  $data['workbench_moderation_states']['description'] = array(
    'title' => t('Moderation state description'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  $data['workbench_moderation_states']['weight'] = array(
    'title' => t('Moderation state order'),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // @todo do we still need these virtual fields?
  // Declare virtual fields on the {node} table.
  $data['node']['workbench_moderation_moderated_type'] = array(
    'group' => t('Workbench Moderation'),
    'title' => t('Type is moderated'),
    'help' => t('Whether the content type is moderated.'),
    'real field' => 'type',
    'filter' => array(
      'handler' => 'workbench_moderation_handler_filter_moderated_type',
      'label' => t('Type is moderated'),
      'type' => 'yes-no',
    ),
  );
  return $data;

}