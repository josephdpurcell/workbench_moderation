<?php

/**
 * @file
 *  Content moderation views integration for Workbench.
 */

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
 * Implements hook_views_data().
 *
 */
function workbench_moderation_views_data_alter(&$data) {
  // unlike State Flow, Workbench Moderation knows its states and can provide
  // them as options in Views
  $data['state_flow_states']['state']['title'] = t("Workbench State Filter");
  $data['state_flow_states']['state']['help'] = t("Use the States defined in Workbench Moderation to filter revisions");
  $data['state_flow_states']['state']['filter'] = array(
    'handler' => 'workbench_moderation_handler_filter_state',
    'label' => t('Current State Filter'),
    'type' => 'select',
  );

  return $data;

}
