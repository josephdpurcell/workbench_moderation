<?php

class workbenchModeration extends StateFlow {

  public function init() {

    $states = workbench_moderation_state_labels();

    foreach ($states as $state_name => $state_label) {
      $state_array = array(
        'title' => $state_label,
      );

      if ($state_name === 'published') {
        $state_array['on_enter'] = array($this, 'on_enter_published');
        $state_array['on_exit'] = array($this, 'on_exit_published');
      }
      $this->create_state($state_name, $state_array);
    }

    ctools_include('export');
    $workbench_events = ctools_export_load_object('workbench_events');

    foreach ($workbench_events as $workbench_event) {

      $origins = array();

      foreach($workbench_event->origin_states as $key => $state_value) {

        // $state_value might be 0.
        // This transformation is a little annoying. It might be better to fix
        // This in the validation of saving workbench_events.
        if (!empty($state_value)) {
          $origins[$key] = $state_value;
        }
      }

      $event_array = array(
        'origin' => $origins,
        'target' => $workbench_event->target_state,
        'guard' => 'workbench_moderation_guard',
        'title' => $workbench_event->admin_title,
      );

      // Initialize events.
      $this->create_event($workbench_event->name, $event_array);
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
      $this->events[$key] = new workbench_moderation_Event($key, $this, $options);
    }

    return $this->events[$key];
  }
}

class workbench_moderation_Event extends StateFlow_Event {
}
