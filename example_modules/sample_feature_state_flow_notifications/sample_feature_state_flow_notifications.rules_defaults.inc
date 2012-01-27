<?php
/**
 * @file
 * sample_feature_state_flow_notifications.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function sample_feature_state_flow_notifications_default_rules_configuration() {
  $items = array();
  $items['rules_state_flow_email_to_user'] = entity_import('rules_config', '{ "rules_state_flow_email_to_user" : {
      "LABEL" : "State_flow_email_to_user",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "state_flow" ],
      "ON" : [ "state_flow_event_fired" ],
      "IF" : [
        { "entity_has_field" : {
            "entity" : [ "state-flow-history-entity" ],
            "field" : "field_stateflow_next_editor"
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "state-flow-history-entity:field-stateflow-next-editor:mail" ],
            "subject" : "This is a State Flow notification: node [node:nid] just change to state: [state-flow-history-entity:state]",
            "message" : "This node was transitioned\\r\\n\\r\\n[node:edit-url]\\r\\n[node:title]"
          }
        }
      ]
    }
  }');
  return $items;
}
