<?php
/**
 * @file
 * workbench_workflows_sample_feature.ctools_rulesets.inc
 */

/**
 * Implements hook_default_workbench_events().
 */
function workbench_workflows_sample_feature_default_workbench_events() {
  $export = array();

  $ruleset = new stdClass;
  $ruleset->disabled = FALSE; /* Edit this to true to make a default ruleset disabled initially */
  $ruleset->api_version = 1;
  $ruleset->name = 'draft';
  $ruleset->target_state = 'draft';
  $ruleset->origin_states = array(
    'needs_review' => 'needs_review',
    'published' => 'published',
    'draft' => 0,
  );
  $ruleset->editor_title = '';
  $ruleset->admin_title = 'Going to Draft (defined by workbench_events)';
  $ruleset->admin_description = '';
  $ruleset->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $ruleset->contexts = array();
  $ruleset->relationships = array();
  $ruleset->access = array(
    'logic' => 'and',
  );
  $export['draft'] = $ruleset;

  $ruleset = new stdClass;
  $ruleset->disabled = FALSE; /* Edit this to true to make a default ruleset disabled initially */
  $ruleset->api_version = 1;
  $ruleset->name = 'needs_review';
  $ruleset->target_state = 'needs_review';
  $ruleset->origin_states = array(
    'draft' => 'draft',
    'published' => 'published',
    'needs_review' => 0,
  );
  $ruleset->editor_title = '';
  $ruleset->admin_title = 'Going to Needs Review (defined by workbench_events)';
  $ruleset->admin_description = '';
  $ruleset->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $ruleset->contexts = array();
  $ruleset->relationships = array();
  $ruleset->access = array(
    'logic' => 'and',
  );
  $export['needs_review'] = $ruleset;

  $ruleset = new stdClass;
  $ruleset->disabled = FALSE; /* Edit this to true to make a default ruleset disabled initially */
  $ruleset->api_version = 1;
  $ruleset->name = 'published';
  $ruleset->target_state = 'published';
  $ruleset->origin_states = array(
    'draft' => 'draft',
    'needs_review' => 'needs_review',
    'published' => 0,
  );
  $ruleset->editor_title = '';
  $ruleset->admin_title = 'Going to Published (defined by workbench_events)';
  $ruleset->admin_description = '';
  $ruleset->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $ruleset->contexts = array();
  $ruleset->relationships = array();
  $ruleset->access = array(
    'logic' => 'and',
  );
  $export['published'] = $ruleset;

  return $export;
}

/**
 * Implements hook_default_workbench_states().
 */
function workbench_workflows_sample_feature_default_workbench_states() {
  $export = array();

  $ruleset = new stdClass;
  $ruleset->disabled = FALSE; /* Edit this to true to make a default ruleset disabled initially */
  $ruleset->api_version = 1;
  $ruleset->name = 'draft';
  $ruleset->editor_title = '';
  $ruleset->admin_title = 'Draft (defined by workbench_states)';
  $ruleset->admin_description = '';
  $ruleset->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $ruleset->contexts = array();
  $ruleset->relationships = array();
  $ruleset->access = array(
    'logic' => 'and',
  );
  $export['draft'] = $ruleset;

  $ruleset = new stdClass;
  $ruleset->disabled = FALSE; /* Edit this to true to make a default ruleset disabled initially */
  $ruleset->api_version = 1;
  $ruleset->name = 'needs_review';
  $ruleset->editor_title = '';
  $ruleset->admin_title = 'Needs Review (defined by workbench_states)';
  $ruleset->admin_description = '';
  $ruleset->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $ruleset->contexts = array();
  $ruleset->relationships = array();
  $ruleset->access = array(
    'logic' => 'and',
  );
  $export['needs_review'] = $ruleset;

  $ruleset = new stdClass;
  $ruleset->disabled = FALSE; /* Edit this to true to make a default ruleset disabled initially */
  $ruleset->api_version = 1;
  $ruleset->name = 'published';
  $ruleset->editor_title = '';
  $ruleset->admin_title = 'Published (defined by workbench_states)';
  $ruleset->admin_description = '';
  $ruleset->requiredcontexts = array(
    0 => array(
      'identifier' => 'Node',
      'keyword' => 'node',
      'name' => 'entity:node',
      'id' => 1,
    ),
  );
  $ruleset->contexts = array();
  $ruleset->relationships = array();
  $ruleset->access = array(
    'logic' => 'and',
  );
  $export['published'] = $ruleset;

  return $export;
}
