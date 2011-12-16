<?php

$plugin = array(
  'schema' => 'workbench_events',
  'access' => 'administer workbench events',

  'menu' => array(
    'menu prefix' => 'admin/config/workbench/events',
    'menu item' => 'workbench-events',
    'menu title' => 'Workbench Events',
    'menu description' => '',
  ),

  'title singular' => t('event'),
  'title singular proper' => t('Event'),
  'title plural' => t('events'),
  'title plural proper' => t('Events'),

  'handler' => 'workbench_events_ui',

  'use wizard' => TRUE,
  'form info' => array(
    'order' => array(
      'basic' => t('Basic information'),
      'context' => t('Contexts'),
      'rules' => t('Rules'),
    ),
  ),
);
