<?php
/**
 * @file
 * workbench_workflows_sample_feature.workbench_events.inc
 */

/**
 * Implements hook_default_workbench_events().
 */
function workbench_workflows_sample_feature_default_workbench_events() {
  $export = array();

  $event = new stdClass;
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'draft';
  $event->target_state = 'draft';
  $event->origin_states = array(
    'needs_review' => 'needs_review',
    'published' => 'published',
    'draft' => 0,
  );
  $event->editor_title = '';
  $event->admin_title = 'Going to Draft (defined by workbench_events)';
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
  $event->access = array();
  $export['draft'] = $event;

  $event = new stdClass;
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'needs_review';
  $event->target_state = 'needs_review';
  $event->origin_states = array(
    'draft' => 'draft',
    'published' => 'published',
    'needs_review' => 0,
  );
  $event->editor_title = '';
  $event->admin_title = 'Going to Needs Review (defined by workbench_events)';
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
  $event->access = array();
  $export['needs_review'] = $event;

  $event = new stdClass;
  $event->disabled = FALSE; /* Edit this to true to make a default event disabled initially */
  $event->api_version = 1;
  $event->name = 'published';
  $event->target_state = 'published';
  $event->origin_states = array(
    'draft' => 'draft',
    'needs_review' => 'needs_review',
    'published' => 0,
  );
  $event->editor_title = '';
  $event->admin_title = 'Going to Published (defined by workbench_events)';
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
  $event->access = array();
  $export['published'] = $event;

  return $export;
}
