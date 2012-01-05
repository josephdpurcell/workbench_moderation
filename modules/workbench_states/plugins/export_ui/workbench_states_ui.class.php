<?php

class workbench_states_ui extends ctools_export_ui {

  function edit_form(&$form, &$form_state) {
  // Get the basic edit form
  parent::edit_form($form, $form_state);

    $form['target_state'] = array(
      '#type' => 'select',

      '#options' => workbench_moderation_state_labels(),
        '#default_value' => $form_state['item']->target_state,
      '#title' => t('Target State'),
      '#description' => t(""),
    );

    $form['origin_states'] = array(
      '#type' => 'checkboxes',
      '#options' => workbench_moderation_state_labels(),
      '#default_value' => $form_state['item']->origin_states,
      '#title' => t('Origin States'),
      '#description' => t(""),
    );
  }

  /**
   * Validate submission of the mini panel edit form.
   */
  function edit_form_basic_validate($form, &$form_state) {
    parent::edit_form_validate($form, $form_state);
    // Need to validate target and origin_states

// if (preg_match("/[^A-Za-z0-9 ]/", $form_state['values']['category'])) {
     // form_error($form['category'], t('Categories may contain only alphanumerics or spaces.'));
   // }
  }

  function edit_form_submit(&$form, &$form_state) {
    parent::edit_form_submit($form, $form_state);
    //$form_state['item']->target_state = $form_state['values']['target_state'];
  }


  function edit_form_context(&$form, &$form_state) {

    // Force setting of the node required context.
    // This is a bad way to do this. Works for now.
    $form_state['item']->requiredcontexts = array(
      0 => array(
          'identifier' => 'Node',
          'keyword' => 'node',
          'name' => 'entity:node',
          'id' => 1
        )
     );


    ctools_include('context-admin');
    ctools_context_admin_includes();
    ctools_add_css('ruleset');




    // Set this up and we can use CTools' Export UI's built in wizard caching,
    // which already has callbacks for the context cache under this name.
    $module = 'export_ui::' . $this->plugin['name'];
    $name = $this->edit_cache_get_key($form_state['item'], $form_state['form type']);


    ctools_context_add_relationship_form($module, $form, $form_state, $form['relationships_table'], $form_state['item'], $name);
  }

  function edit_form_rules(&$form, &$form_state) {
    // The 'access' UI passes everything via $form_state, unlike the 'context' UI.
    // The main difference is that one is about 3 years newer than the other.
    ctools_include('context');
    ctools_include('context-access-admin');

    $form_state['access'] = $form_state['item']->access;
    $form_state['contexts'] = ctools_context_load_contexts($form_state['item']);

    $form_state['module'] = 'ctools_export_ui';
    $form_state['callback argument'] = $form_state['object']->plugin['name'] . ':' . $form_state['object']->edit_cache_get_key($form_state['item'], $form_state['form type']);
    $form_state['no buttons'] = TRUE;

    $form = ctools_access_admin_form($form, $form_state);
  }

  function edit_form_rules_submit(&$form, &$form_state) {
    $form_state['item']->access['logic'] = $form_state['values']['logic'];
  }
}
