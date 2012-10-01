<?php

/**
 * @file
 *
 * Administrative functions for workbench_workflows.
 */

function workbench_workflows_admin_page() {

  $output = '';

  $item = menu_get_item();
  if ($content = system_admin_menu_block($item)) {

    // @todo, does this page need a theme function?

    // If there are no states, events, or workflows, show a form to install
    // a default configuration.
    $states = workbench_workflows_load_all('states');
    $events = workbench_workflows_load_all('events');
    $workflows = workbench_workflows_load_all('workflows');

    if (empty($states) && empty($events) && empty($workflows)) {
      $form = drupal_get_form('workbench_workflows_install_default_workflow_form');
      $output = drupal_render($form);
    }

    $output .= theme('admin_block_content', array('content' => $content));
  }
  else {
    $output .= t('You do not have any administrative items.');
  }
  return $output;
}

/**
 * Provides a form to install the default workflow.
 */
function workbench_workflows_install_default_workflow_form($form, &$form_state) {
  $form = array();

  // @todo Would it be overkill to do a theme function for this form so that <p> tags
  // are not added in a normal function?
  $form['message'] = array(
    '#markup' => '<p>' . t('There are no states, events, or workflows yet on this site. Would you like to install a default configuration?') . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Install the default workflow')
  );

  return $form;
}

/**
 * Actually installs the default configuration.
 *
 * submit handler for workbench_workflows_install_default_workflow_form().
 */
function workbench_workflows_install_default_workflow_form_submit($form, &$form_state) {
  module_load_include('inc', 'workbench_workflows', 'includes/workbench_workflows.starter');
  workbench_workflows_import_starter_exportables();

  // Notify the user that the default workflow is installed.
  drupal_set_message(t('A default workflow with the states and events of Draft, Needs Review, and Published.'));
}

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
      "menu prefix" => "admin/structure/workbench-workflows",
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
