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

  $transitions = workbench_moderation_transitions();

  foreach ($transitions as $transition) {

    $to_name = $transition->to_name;
    $from_name = $transition->from_name;
    // This is silly.
    $event_name = $from_name . '__' . $transition->to_name;

    $event_array = array(
      'origin' => array(
       $from_name => $from_name),
      'target' => $to_name,
      'guard' => 'workbench_moderation_guard',
      'title' => $to_name,
    );

    // Initialize events.
    $this->create_event($event_name, $event_array);
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

  /**
   * Can this event be used to transition from the specified state?
   */
  public function can_transition_from($state) {
    return in_array($state, $this->options['origin']);
  }
}
