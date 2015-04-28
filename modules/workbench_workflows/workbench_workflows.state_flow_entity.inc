<?php

/**
 * @file
 * Helper function for hook_state_flow_entity_plugins().
 */


/**
 * Helper function for hook_state_flow_entity_plugins().
 */
function _workbench_workflows_state_flow_entity_plugins() {
  $info = array();

  // Load all workflows, events and states.
  $workflows = workbench_workflows_load_all('workflows');
  $event_exportables = workbench_workflows_load_all('events');
  $state_exportables = workbench_workflows_load_all('states');

  // We're just building on top of the state_flow plugins.
  $class_path = drupal_get_path('module', 'state_flow') . '/plugins';

  foreach ($workflows as $workflow) {

    // This array will be built up and included with the state_flow plugin.
    $workflow_options = array();
    $workflow_options['default_state'] = $workflow->default_state;

    // Build up states in a way compatible with state_flow_plugins.
    foreach ($workflow->states as $state_name) {
      // Make sure the load_all() array has the state.
      if (isset($state_exportables[$state_name])) {
        $state = $state_exportables[$state_name];
        $state_array = array(
          'label' => $state->admin_title,
        );

        if ($state->entity_state_change == WORKBENCH_WORKFLOWS_STATE_PUBLISHED) {
          $state_array['on_enter'] = 'on_enter_published';
          $state_array['on_exit'] = 'on_exit_published';
        }
        // Integrate with state flow schedule.
        elseif ($state_name == 'schedule') {
          $state_array['on_exit'] = 'on_exit_scheduled';
        }
        // @todo, this piece should be tested here as well as the unpublished
        // test in state machine.
        elseif ($state->entity_state_change == WORKBENCH_WORKFLOWS_STATE_UNPUBLISHED) {
          $state_array['on_enter'] = 'on_enter_unpublished';
        }
        $workflow_options['states'][$state_name] = $state_array;
      }
    }

    // Build up events in a way compatible with state_flow_plugins.
    foreach ($workflow->events as $event_name) {

      $origins = array();
      // Make sure the load_all() array has the event.
      if (isset($event_exportables[$event_name])) {
        $event = $event_exportables[$event_name];
        // Ensure only active origin_states are available.
        $origins = array_filter($event->origin_states);

        $target_state = $event->target_state;

        $event_array = array(
          'origin' => $origins,
          'target' => $target_state,
          'guard' => 'workbench_workflows_guard',
          'label' => $event->admin_title,
        );

        $workflow_options['events'][$event_name] = $event_array;
      }
    }

    $info['workbench_workflows__' . $workflow->name] = array(
      'handler' => array(
        // @todo, Once StateFlow can handle non-nodes, these properties will have
        // to respond to something in the $workflow variable to change the class
        // name and the file, parent etc.
        'class' => 'StateFlowNode',
        'file' => 'state_flow_node.inc',
        'path' => $class_path,
        'parent' => 'state_flow_entity',
        'workflow_options' => $workflow_options,
        'entity_type' => 'node',

        // @todo, make this configurable in workflow exportables.
        // @todo, should this key be inside "handler" or at the top level of the plugin?
        'event_form_options' => array(
          'event_element_label' => t('Change State'),
          'require_log_message' => FALSE,
        ),

      ),
    );
  }

  // A plugin for ignoring workflows.
  $info['workbench_workflows_ignore'] = array(
    'handler' => array(
      'class' => 'WorkbenchWorkflowsIgnore',
      'file' => 'workbench_workflows_ignore.inc',
      'path' => drupal_get_path('module', 'workbench_workflows') . '/plugins/state_flow_entity',
      'parent' => 'state_flow_node',
      'workflow_options' => array(),
      'entity_type' => 'node',
      'event_form_options' => array(),
    ),
  );
  return $info;
}

/**
 * Return the appropriate workflow for a node.
 */
function workbench_workflows_select_workflow($entity) {

  $workflows = workbench_workflows_load_enabled('workflows');
  foreach ($workflows as $workflow) {
    if (workbench_workflows_exportable_access($entity, $workflow, 'workflows')) {
      // Return the first workflow for which access returns TRUE.
      return $workflow;
    }
  }
  return FALSE;
}
