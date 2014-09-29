<?php

/**
 * @file
 *
 * Functions to install exportables.
 */

/**
 * Save the starter exportables to the database.
 */
function workbench_workflows_import_starter_exportables() {

  ctools_include('export');
  $exportables = _workbench_workflows_starter_exportables();
  foreach ($exportables as $exportable_type => $set_of_exportables) {
    foreach ($set_of_exportables as $exportable_machine_name => $exportable) {
      ctools_export_crud_save('workbench_workflows_' . $exportable_type, $exportable);
    }
  }
}

/**
 * Returns an array of exported starter states, events, and one workflow.
 */
function _workbench_workflows_starter_exportables() {
  $events = array();
  $exportables = array();

  $event = new stdClass();
  // The export_type property was not included when I copied this from a features
  // module. ctools_export_crud_save() generates a PHP notice without it.
  $event->export_type = 'workbench_workflows_events';
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'draft';
  $event->editor_title = '';
  $event->admin_title = 'Draft';
  $event->admin_description = '';
  $event->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $event->contexts = array();
  $event->relationships = array();
  $event->access = array(
    'logic' => 'and',
  );
  $event->weight = 0;
  $event->target_state = 'draft';
  $event->origin_states = array(
    'draft' => 'draft',
    'needs_review' => 'needs_review',
    'published' => 'published',
  );
  $events['draft'] = $event;

  $event = new stdClass();
  // The export_type property was not included when I copied this from a features
  // module. ctools_export_crud_save() generates a PHP notice without it.
  $event->export_type = 'workbench_workflows_events';
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'needs_review';
  $event->editor_title = '';
  $event->admin_title = 'Needs Review';
  $event->admin_description = '';
  $event->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $event->contexts = array();
  $event->relationships = array();
  $event->access = array(
    'logic' => 'and',
  );
  $event->weight = 0;
  $event->target_state = 'needs_review';
  $event->origin_states = array(
    'draft' => 'draft',
    'needs_review' => 'needs_review',
    'published' => 'published',
  );
  $events['needs_review'] = $event;

  $event = new stdClass();
  // The export_type property was not included when I copied this from a features
  // module. ctools_export_crud_save() generates a PHP notice without it.
  $event->export_type = 'workbench_workflows_events';
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'published';
  $event->editor_title = '';
  $event->admin_title = 'Published';
  $event->admin_description = '';
  $event->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $event->contexts = array();
  $event->relationships = array();
  $event->access = array(
    'logic' => 'and',
  );
  $event->weight = 0;
  $event->target_state = 'published';
  $event->origin_states = array(
    'draft' => 'draft',
    'needs_review' => 'needs_review',
    'published' => 'published',
  );
  $events['published'] = $event;
  $exportables['events'] = $events;


  $states = array();

  $state = new stdClass();
  // The export_type property was not included when I copied this from a features
  // module. ctools_export_crud_save() generates a PHP notice without it.
  $state->export_type = 'workbench_workflows_states';
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'draft';
  $state->editor_title = '';
  $state->admin_title = 'Draft';
  $state->admin_description = '';
  $state->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $state->contexts = array();
  $state->relationships = array();
  $state->access = array();
  $state->weight = 0;
  $state->entity_state_change = WORKBENCH_WORKFLOWS_STATE_UNCHANGED;
  $states['draft'] = $state;

  $state = new stdClass();
  // The export_type property was not included when I copied this from a features
  // module. ctools_export_crud_save() generates a PHP notice without it.
  $state->export_type = 'workbench_workflows_states';
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'needs_review';
  $state->editor_title = '';
  $state->admin_title = 'Needs Review';
  $state->admin_description = '';
  $state->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $state->contexts = array();
  $state->relationships = array();
  $state->access = array();
  $state->weight = 0;
  $state->entity_state_change = WORKBENCH_WORKFLOWS_STATE_UNCHANGED;
  $states['needs_review'] = $state;

  $state = new stdClass();
  // The export_type property was not included when I copied this from a features
  // module. ctools_export_crud_save() generates a PHP notice without it.
  $state->export_type = 'workbench_workflows_states';
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'published';
  $state->editor_title = '';
  $state->admin_title = 'Published';
  $state->admin_description = '';
  $state->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $state->contexts = array();
  $state->relationships = array();
  $state->access = array();
  $state->weight = 0;
  $state->entity_state_change = WORKBENCH_WORKFLOWS_STATE_PUBLISHED;
  $states['published'] = $state;

  $exportables['states'] = $states;


  $workflows = array();

  $workflow = new stdClass();
  // The export_type property was not included when I copied this from a features
  // module. ctools_export_crud_save() generates a PHP notice without it.
  $workflow->export_type = 'workbench_workflows_workflows';
  $workflow->disabled = FALSE; /* Edit this to true to make a default workflow disabled initially */
  $workflow->api_version = 1;
  $workflow->name = 'default_workflow';
  $workflow->editor_title = '';
  $workflow->admin_title = 'Default Workflow';
  $workflow->admin_description = '';
  $workflow->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $workflow->contexts = array();
  $workflow->relationships = array();
  $workflow->access = array();
  $workflow->weight = 2;
  $workflow->category = '';
  $workflow->states = array(
    'draft' => 'draft',
    'needs_review' => 'needs_review',
    'published' => 'published',
  );
  $workflow->events = array(
    'draft' => 'draft',
    'needs_review' => 'needs_review',
    'published' => 'published',
  );
  $workflows['sample_workflow'] = $workflow;

    $exportables['workflows'] = $workflows;

  return $exportables;
}
