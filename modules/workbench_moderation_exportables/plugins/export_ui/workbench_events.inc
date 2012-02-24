<?php

$plugin = array(
  'schema' => 'workbench_moderation_exportables_events',
  'access' => 'administer_workbench_moderation_exportables',

  'menu' => array(
    'menu prefix' => 'admin/structure/wm-exportables',
    'menu item' => 'workbench-events',
    'menu title' => 'Workbench Events',
    'menu description' => 'Add, edit or delete Workbench Events.',
  ),

  'title singular' => t('workbench event'),
  'title singular proper' => t('Workbench Event'),
  'title plural' => t('workbench events'),
  'title plural proper' => t('Workbench Events'),

  'handler' => 'workbench_events_ui',

  'use wizard' => TRUE,
  'form info' => array(
    'order' => array(
      'basic' => t('Basic information'),
      'context' => t('Contexts'),
      'access' => t('Access'),
    ),
  ),
);
