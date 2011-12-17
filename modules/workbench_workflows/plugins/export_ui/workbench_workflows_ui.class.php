<?php

class workbench_workflows_ui extends ctools_export_ui {
  function init($plugin) {
    parent::init($plugin);
    ctools_include('context');
  }
/*
  function list_form(&$form, &$form_state) {

    parent::list_form($form, $form_state);

    foreach ($this->items as $item) {
      $categories[$item->category] = $item->category ? $item->category : t('workbench workflows');
    }

    $form['top row']['category'] = array(
      '#type' => 'select',
      '#title' => t('Category'),
      '#options' => $categories,
      '#default_value' => 'all',
      '#weight' => -10,
    );

  }

  function list_filter($form_state, $item) {
    if ($form_state['values']['category'] != 'all' && $form_state['values']['category'] != $item->category) {
      return TRUE;
    }


    return parent::list_filter($form_state, $item);
  }
*/
  function list_sort_options() {
    return array(
      'disabled' => t('Enabled, title'),
      'title' => t('Title'),
      'name' => t('Name'),
      'category' => t('Category'),
      'storage' => t('Storage'),
      'weight' => t('Weight'),
    );
  }

  function list_build_row($item, &$form_state, $operations) {
    // Set up sorting
    switch ($form_state['values']['order']) {
      case 'disabled':
        $this->sorts[$item->name] = empty($item->disabled) . $item->admin_title;
        break;
      case 'title':
        $this->sorts[$item->name] = $item->admin_title;
        break;
      case 'name':
        $this->sorts[$item->name] = $item->name;
        break;
      case 'category':
        $this->sorts[$item->name] = ($item->category ? $item->category : t('workbench workflows')) . $item->admin_title;
        break;
      case 'weight':
        $this->sorts[$item->name] = $item->weight;
        break;
      case 'storage':
        $this->sorts[$item->name] = $item->type . $item->admin_title;
        break;
    }

    $category = $item->category ? check_plain($item->category) : t('workbench workflows');

    $this->rows[$item->name] = array(
      'data' => array(
        array('data' => check_plain($item->admin_title), 'class' => array('ctools-export-ui-title')),
        array('data' => check_plain($item->name), 'class' => array('ctools-export-ui-name')),
        array('data' => $category, 'class' => array('ctools-export-ui-category')),
        array('data' => $item->type, 'class' => array('ctools-export-ui-storage')),
        array('data' => $item->weight, 'class' => array('ctools-export-ui-weight')),
        array('data' => theme('links', array('links' => $operations)), 'class' => array('ctools-export-ui-operations')),
      ),
      'title' => !empty($item->admin_description) ? check_plain($item->admin_description) : '',
      'class' => array(!empty($item->disabled) ? 'ctools-export-ui-disabled' : 'ctools-export-ui-enabled'),
    );
  }

  function list_table_header() {
    return array(
      array('data' => t('Title'), 'class' => array('ctools-export-ui-title')),
      array('data' => t('Name'), 'class' => array('ctools-export-ui-name')),
      array('data' => t('Category'), 'class' => array('ctools-export-ui-category')),
      array('data' => t('Storage'), 'class' => array('ctools-export-ui-storage')),
      array('data' => t('Weight'), 'class' => array('ctools-export-ui-weight')),
      array('data' => t('Operations'), 'class' => array('ctools-export-ui-operations')),
    );
  }

  function edit_form(&$form, &$form_state) {
    // Get the basic edit form
    parent::edit_form($form, $form_state);

    $form['title']['#title'] = t('Title');
    $form['title']['#description'] = t('The title for this workbench workflow.');

    $form['states'] = array(
      '#type' => 'checkboxes',
      '#options' => workbench_moderation_state_labels(),
      '#default_value' => $form_state['item']->states,
      '#title' => t('States'),
      '#description' => t("States available in this workflow."),
    );

    $form['weight'] = array(
      '#type' => 'textfield',
      '#default_value' => $form_state['item']->weight,
      '#title' => t('Weight'),
      '#element_validate' => array('element_validate_integer_positive'),
    );
  }

  /**
   * Validate submission of the workbench workflow edit form.
   */
  function edit_form_basic_validate($form, &$form_state) {
    parent::edit_form_validate($form, $form_state);
  //  if (preg_match("/[^A-Za-z0-9 ]/", $form_state['values']['category'])) {
//      form_error($form['category'], t('Categories may contain only alphanumerics or spaces.'));
   // }
  }

  function edit_form_submit(&$form, &$form_state) {
    parent::edit_form_submit($form, $form_state);
  }

  function edit_form_events(&$form, &$form_state) {

    $available_states = array();
    foreach ($form_state['item']->states as $key => $value) {
      if (!empty($value)) {
        $available_states[$key] =$value;
      }
    }

    ctools_include('export');
    $workbench_events = ctools_export_load_object('workbench_events');
    $event_options = array();
    $unavailable_events = array();
    $unavailable_text_string = '';
    $unavailable_events_replacements = array();

    foreach ($workbench_events as $workbench_event) {

      // @@TODO
      // Exclude events when there is not an origin state in the workflow.
      if (in_array($workbench_event->target_state, $available_states)) {
        $event_options[$workbench_event->name] = $workbench_event->admin_title;
      } else {
        $unavailable_text_string .= '%' . $workbench_event->name . ', ';
        $unavailable_events[$workbench_event->name] = $workbench_event->admin_title;
        $unavailable_events_replacements['%' . $workbench_event->name] = $workbench_event->admin_title;
      }
    }

    $form['events'] = array(
      '#type' => 'checkboxes',
      '#options' => $event_options,
      '#default_value' => $form_state['item']->events,
      '#title' => t('Events'),
      // @@TODO
      // Handle pluralization of event/events
      '#description' => t("Unavailable events include: " . $unavailable_text_string, $unavailable_events_replacements),
    );
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

    // Set this up and we can use CTools' Export UI's built in wizard caching,
    // which already has callbacks for the context cache under this name.
    $module = 'export_ui::' . $this->plugin['name'];
    $name = $this->edit_cache_get_key($form_state['item'], $form_state['form type']);


    ctools_context_add_relationship_form($module, $form, $form_state, $form['relationships_table'], $form_state['item'], $name);
  }

  function edit_form_context_submit(&$form, &$form_state) {
    // Prevent this from going to edit_form_submit();
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
