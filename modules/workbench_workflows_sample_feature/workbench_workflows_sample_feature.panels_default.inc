<?php
/**
 * @file
 * workbench_workflows_sample_feature.panels_default.inc
 */

/**
 * Implements hook_default_workbench_workflows().
 */
function workbench_workflows_sample_feature_default_workbench_workflows() {
  $export = array();

  $workflow = new stdClass;
  $workflow->disabled = FALSE; /* Edit this to true to make a default workflow disabled initially */
  $workflow->api_version = 1;
  $workflow->name = 'main_workflow';
  $workflow->category = '';
  $workflow->admin_title = 'main_workflow';
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
  $workflow->access = array(
    'logic' => 'and',
  );
  $display = new ;
  $display->layout = '';
  $display->layout_settings = '';
  $display->panel_settings = '';
  $display->cache = '';
  $display->title = '';
  $display->content = array();
  $display->panels = array();
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $mini->display = $display;
  $export['main_workflow'] = $workflow;

  return $export;
}
