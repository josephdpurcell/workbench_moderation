<?php

/**
 * @file functions related to node pages.
 */

/**
 * Displays the current draft the node, if it is not published.
 *
 * @param $node
 *   The node being acted upon.
 *
 * @return
 *   A fully themed node page.
 */
function workbench_moderation_node_view_draft($node) {
  //get draft node
  $draft_node = state_flow_entity_get_active_revision($node, 'node');
  //return themed draft node page
  return workbench_moderation_router_item_page_callback($draft_node);
}

/**
 * Get the menu router item for nodes.
 *
 * @param $node
 *   The node being acted upon.
 * @return
 *   A fully themed node page.
 */
function workbench_moderation_router_item_page_callback($node) {
  $router_item = menu_get_item('node/' . $node->nid);
  if ($router_item['include_file']) {
    require_once DRUPAL_ROOT . '/' . $router_item['include_file'];
  }

  // Call whatever function is assigned to the main node path but pass the
  // current node as an argument. This approach allows for the reuse of of Panel
  // definition acting on node/%node.
  return $router_item['page_callback']($node);
}

/**
 * Displays a specific revisison of the node.
 *
 * @param $node
 *   The node being acted upon.
 *
 * @return
 *   A fully themed node page.
 */
function workbench_moderation_node_view_revision($node) {
  return workbench_moderation_router_item_page_callback($node);
}
