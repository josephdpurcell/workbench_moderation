<?php

class workbenchStateflow extends StateFlow {

  public function init() {

    $workflow = workbench_workflows_select_workflow($this->object);

    // @todo it'd be nice to to $workflow->states();
    $states = $workflow->states;
    $state_exportables = workbench_states_load_all();

    foreach ($states as $state_name => $state) {
      $state_array = array(
        'title' => $state_exportables[$state_name]->admin_title,
      );

      if ($state_name === 'published') {
        $state_array['on_enter'] = array($this, 'on_enter_published');
        $state_array['on_exit'] = array($this, 'on_exit_published');
      }

      $this->create_state($state_name, $state_array);
    }

    ctools_include('export');
    $event_exportables = ctools_export_load_object('workbench_events');

    foreach ($workflow->events as $event_name => $event) {

      $origins = array();

      foreach($event_exportables[$event_name]->origin_states as $key => $state_value) {

        // $state_value might be 0.
        // This transformation is a little annoying. It might be better to fix
        // This in the validation of saving workbench_events.
        if (!empty($state_value)) {
          $origins[$key] = $state_value;
        }
      }

      $event_array = array(
        'origin' => $origins,
        'target' => $event_exportables[$event_name]->target_state,
        'guard' => 'workbench_stateflow_guard',
        'title' => $event_exportables[$event_name]->admin_title,
      );

      // Initialize events.
      $this->create_event($event_exportables[$event_name]->name, $event_array);
    }
  }

  public function on_event_fail($event) {
    $key = array_search($event, $this->events);
    drupal_set_message(t('Could not transition node using %event event.', array('%event' => $key)), 'error');
  }

  public function get_event($key) {
    if (!array_key_exists($key, $this->events)) {
      return FALSE;
    }

    if (is_array($this->events[$key])) {
      $options = $this->events[$key];
      $this->events[$key] = new workbench_stateflow_Event($key, $this, $options);
    }

    return $this->events[$key];
  }
}

/**
 * Not sure if this class will be needed.
 */
class workbench_stateflow_Event extends StateFlow_Event {
}