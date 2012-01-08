<?php

/**
 * @file
 * Define a new StateMachine for the node
 */

/**
 * Implements hook_workbench_machine_plugins().
 *
 * Define the ctools plugin to add a new state machine type for the node workflow.
 * In this example we are Add a "reviewed" state to the StateFlow class.
 */

/**
 * Implements hook_workbench_machine_plugins().
 */
function hook_workbench_machine_plugins() {
  $info = array();
  $path = drupal_get_path('module', 'workbench_machine') . '/plugins';
  $info['workbench_machine_test'] = array(
    'handler' => array(
      'class' => 'StateFlowTest',
      'file' => 'workbench_machine.inc',
      'path' => $path,
      'parent' => 'workbench_machine'
    ),
  );
  return $info;
}

