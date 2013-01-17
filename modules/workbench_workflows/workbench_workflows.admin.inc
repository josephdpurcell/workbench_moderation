<?php

/**
 * @file
 *
 * Administrative functions for workbench_workflows.
 */

/**
 * @param string $type
 *   Allowed values are 'state', 'event', and 'workflow'
 * @return array
 */
function workbench_workflows_export_ui_base_plugin($type) {

  $plural = $type . 's';

  $plugin = array(
    "schema" => "workbench_workflows_$plural",
    "access" => "administer_workbench_workflows",

    "menu" => array(
      "menu prefix" => "admin/config/workflow/workbench-workflows",
      "menu item" => $plural,
      "menu title" => "Workbench " . $plural,
      "menu description" => "Add, edit or delete Workbench " . drupal_ucfirst($plural),
    ),

    "title singular" => t("workbench $type"),
    "title singular proper" => t("Workbench " . drupal_ucfirst($type)),
    "title plural" => t("workbench $type"),
    "title plural proper" => t("Workbench " . drupal_ucfirst($plural)),

    "handler" => "workbench_" . $plural . "_ui",

    "use wizard" => TRUE,
    "form info" => array(
      "order" => array(
        "basic" => t("Basic information"),
        "context" => t("Contexts"),
        "access" => t("Access"),
      ),
    ),
  );

  return $plugin;
}
