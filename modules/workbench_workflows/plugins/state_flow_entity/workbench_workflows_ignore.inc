<?php

/**
 * @file
 *   A class to mark a node as ignored by State Machine / Workbench Workflows.
 */

class WorkbenchWorkflowsIgnore extends StateFlowNode {

  public function init($workflow = array()) {
  }

  public function ignore() {
    return TRUE;
  }
}