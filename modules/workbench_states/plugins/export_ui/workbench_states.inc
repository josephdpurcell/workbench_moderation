<?php

$plugin = array(
  'schema' => 'workbench_states',
  'access' => 'administer workbench states',

  'menu' => array(
    'menu prefix' => 'admin/config/workbench/states',
    'menu item' => 'workbench-states',
    'menu title' => 'Workbench states',
    'menu description' => '',
  ),

  'title singular' => t('state'),
  'title singular proper' => t('State'),
  'title plural' => t('states'),
  'title plural proper' => t('States'),

  'handler' => 'workbench_states_ui',

  'use wizard' => TRUE,
  'form info' => array(
    'order' => array(
      'basic' => t('Basic information'),
      'context' => t('Contexts'),
      'rules' => t('Rules'),
    ),
  ),
);
