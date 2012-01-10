<?php

$plugin = array(
  'schema' => 'workbench_states',
  'access' => 'administer workbench states',

  'menu' => array(
    'menu prefix' => 'admin/config/workbench/states',
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
