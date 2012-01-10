<?php
/**
 * @file
 * workbench_workflows_sample_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function workbench_workflows_sample_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ctools" && $api == "ctools_rulesets") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "workbench_workflows" && $api == "panels_default") {
    return array("version" => "1");
  }
}
