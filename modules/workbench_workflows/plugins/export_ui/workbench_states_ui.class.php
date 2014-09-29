<?php

/**
 * @file
 *
 * The UI class for states exportables.
 */

module_load_include('php', 'workbench_workflows', 'plugins/export_ui/workbench_base_ui.class');

class workbench_states_ui extends workbench_base_ui {

  function edit_form(&$form, &$form_state) {
    // Get the basic edit form.
    parent::edit_form($form, $form_state);

    $form['entity_state_change'] = array(
      '#type' => 'radios',
      '#default_value' => (isset($form_state['item']->entity_state_change)) ? $form_state['item']->entity_state_change : WORKBENCH_WORKFLOWS_STATE_UNCHANGED,
      '#title' => t('Entity status'),
      '#options' => array(
        WORKBENCH_WORKFLOWS_STATE_UNCHANGED => t("Don't change status"),
        WORKBENCH_WORKFLOWS_STATE_UNPUBLISHED => t('Unpublished'),
        WORKBENCH_WORKFLOWS_STATE_PUBLISHED => t('Published'),
      ),
      '#description' => t('Defines the status the entity will have when entering this moderation state.'),
    );
  }
}
