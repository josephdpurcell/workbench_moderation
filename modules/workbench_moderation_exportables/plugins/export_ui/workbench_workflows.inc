<?php

  module_load_include('inc', 'workbench_moderation_exportables', 'workbench_moderation_exportables.admin');
  $plugin = workbench_moderation_exportables_export_ui_base_plugin('workflow');

  // Override the form info because workflows have an extra screen.
  $plugin['form info']['order'] = array(
    'basic' => t('Settings'),
    'events' => t('Events'),
    'context' => t('Context'),
    'access' => t('Access'),
  );
