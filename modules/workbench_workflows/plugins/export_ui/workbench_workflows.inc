<?php

$plugin = array(
  'schema' => 'workbench_workflows',
  'access' => 'administer workbench workflows',
  'create access' => 'create workbench workflows',

  'menu' => array(
    'menu item' => 'workbench-workflows',
    'menu title' => 'workbench workflows',
    'menu description' => 'Add, edit or delete workbench workflows, which can be used as blocks or content panes in other panels.',
  ),

  'title singular' => t('workbench workflow'),
  'title singular proper' => t('workbench workflow'),
  'title plural' => t('workbench workflows'),
  'title plural proper' => t('workbench workflows'),

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
      'rules' => t('Rules'),
    ),
    // We have to add this form specially because it's invisible.
    'forms' => array(
      'move' => array(
        'form id' => 'ctools_export_ui_edit_item_wizard_form',
      ),
    ),
  ),

);

