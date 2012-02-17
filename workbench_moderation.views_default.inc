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
