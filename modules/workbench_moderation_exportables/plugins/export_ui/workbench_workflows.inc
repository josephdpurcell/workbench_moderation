<?php

$plugin = array(
  'schema' => 'workbench_moderation_exportables_workflows',
  'access' => 'administer_workbench_moderation_exportables',

  'menu' => array(
    'menu prefix' => 'admin/structure',
    'menu item' => 'workbench-workflows',
    'menu title' => 'Workbench Workflows',
    'menu description' => 'Add, edit or delete Workbench Workflows.',
  ),

  'title singular' => t('workbench workflow'),
  'title singular proper' => t('Workbench Workflow'),
  'title plural' => t('workbench workflows'),
  'title plural proper' => t('Workbench Workflows'),

  'handler' => array(
    'class' => 'workbench_workflows_ui',
    'parent' => 'ctools_export_ui',
  ),

  'use wizard' => TRUE,
  'form info' => array(
    'order' => array(
      'basic' => t('Settings'),
      'events' => t('Events'),
      'context' => t('Context'),
      'access' => t('Access'),
    ),
    // We have to add this form specially because it's invisible.
    'forms' => array(
      'move' => array(
        'form id' => 'ctools_export_ui_edit_item_wizard_form',
      ),
    ),
  ),

);
