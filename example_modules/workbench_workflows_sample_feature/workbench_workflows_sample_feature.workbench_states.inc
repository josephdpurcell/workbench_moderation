<?php
/**
 * @file
 * workbench_workflows_sample_feature.workbench_states.inc
 */

/**
 * Implements hook_default_workbench_states().
 */
function workbench_workflows_sample_feature_default_workbench_states() {
  $export = array();

  $state = new stdClass;
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'draft';
  $state->editor_title = '';
  $state->admin_title = 'Draft (defined by workbench_states)';
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
  $export['draft'] = $state;

  $state = new stdClass;
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'needs_review';
  $state->editor_title = '';
  $state->admin_title = 'Needs Review (defined by workbench_states)';
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
  $export['needs_review'] = $state;

  $state = new stdClass;
  $state->disabled = FALSE; /* Edit this to true to make a default state disabled initially */
  $state->api_version = 1;
  $state->name = 'published';
  $state->editor_title = '';
  $state->admin_title = 'Published (defined by workbench_states)';
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
  $export['published'] = $state;

  return $export;
}
