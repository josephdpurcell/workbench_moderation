<?php
/**
 * @file
 * workbench_workflows_sample_feature.workbench_workflows.inc
 */

/**
 * Implements hook_default_workbench_workflows().
 */
function workbench_workflows_sample_feature_default_workbench_workflows() {
  $export = array();

  $workflow = new stdClass;
  $workflow->disabled = FALSE; /* Edit this to true to make a default workflow disabled initially */
  $workflow->api_version = 1;
  $workflow->name = 'sample_workflow';
  $workflow->category = '';
  $workflow->admin_title = 'sample_workflow (Defined by Workbench Workflows)';
  $workflow->admin_description = '';
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
  $workflow->weight = 0;
  $export['sample_workflow'] = $workflow;

  return $export;
}
