<?php

module_load_include('php', 'workbench_moderation_exportables', 'plugins/export_ui/workbench_base_ui.class');

class workbench_states_ui extends workbench_base_ui {

  function edit_form(&$form, &$form_state) {
    // Get the basic edit form
    parent::edit_form($form, $form_state);
  }
}
