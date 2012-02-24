<?php

$plugin = array(
  'schema' => 'workbench_moderation_exportables_states',
  'access' => 'administer_workbench_moderation_exportables',

  'menu' => array(
    'menu prefix' => 'admin/structure/wm-exportables',
    'menu item' => 'workbench-states',
    'menu title' => 'Workbench States',
    'menu description' => 'Add, edit or delete Workbench States.',
  ),

  'title singular' => t('workbench state'),
  'title singular proper' => t('Workbench State'),
  'title plural' => t('workbench states'),
  'title plural proper' => t('Workbench States'),

  'handler' => 'workbench_states_ui',

  'use wizard' => TRUE,
  'form info' => array(
    'order' => array(
      'basic' => t('Basic information'),
      'context' => t('Contexts'),
      'access' => t('Access'),
    ),
  ),
);
