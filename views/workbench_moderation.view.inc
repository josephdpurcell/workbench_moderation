<?php

/**
 * @file workbench_moderation.view.inc
 * Default view. Provides two tabs on the Workbench, "My Drafts" and "Needs
 * Review", which list the moderation state for content relevant to the current
 * user.
 */

$view = new view;
$view->name = 'workbench_moderation';
$view->description = '';
$view->tag = 'Workbench Moderation';
$view->base_table = 'node_revision';
$view->human_name = 'workbench_moderation';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'Content I\'ve Edited';
$handler->display->display_options['use_more_always'] = TRUE;
$handler->display->display_options['use_more_text'] = 'view all';
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'use workbench_moderation my drafts tab';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
$handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 25, 50, 100, 200';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'nid' => 'nid',
  'nid_1' => 'nid_1',
  'log' => 'log',
  'nothing' => 'nothing',
  'state' => 'state',
  'moderation_actions' => 'moderation_actions',
  'title' => 'title',
  'type' => 'type',
  'name' => 'name',
  'changed' => 'changed',
);
$handler->display->display_options['style_options']['default'] = 'changed';
$handler->display->display_options['style_options']['info'] = array(
  'nid' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'nid_1' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'log' => array(
    'align' => '',
    'separator' => '',
  ),
  'nothing' => array(
    'align' => '',
    'separator' => '',
  ),
  'state' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'moderation_actions' => array(
    'align' => '',
    'separator' => '',
  ),
  'title' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'type' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'changed' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
  ),
);
$handler->display->display_options['style_options']['override'] = 1;
$handler->display->display_options['style_options']['sticky'] = 0;
$handler->display->display_options['style_options']['order'] = 'desc';
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = FALSE;
$handler->display->display_options['empty']['area']['content'] = 'You haven\'t created or edited any content.';
$handler->display->display_options['empty']['area']['format'] = '1';
/* Relationship: Content revision: User */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
/* Relationship: State Flow States: State Flow History Entity */
$handler->display->display_options['relationships']['hid']['id'] = 'hid';
$handler->display->display_options['relationships']['hid']['table'] = 'state_flow_states';
$handler->display->display_options['relationships']['hid']['field'] = 'hid';
$handler->display->display_options['relationships']['hid']['required'] = 0;
/* Field: State Flow States: Revision current state */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'state_flow_states';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['label'] = 'Moderation State';
$handler->display->display_options['fields']['state']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['state']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['state']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['state']['alter']['external'] = 0;
$handler->display->display_options['fields']['state']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['state']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['state']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['state']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['state']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['state']['alter']['more_link'] = 0;
$handler->display->display_options['fields']['state']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['state']['alter']['trim'] = 0;
$handler->display->display_options['fields']['state']['alter']['html'] = 0;
$handler->display->display_options['fields']['state']['element_label_colon'] = 1;
$handler->display->display_options['fields']['state']['element_default_classes'] = 1;
$handler->display->display_options['fields']['state']['hide_empty'] = 0;
$handler->display->display_options['fields']['state']['empty_zero'] = 0;
$handler->display->display_options['fields']['state']['hide_alter_empty'] = 1;
/* Field: Content: Nid */
$handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
$handler->display->display_options['fields']['nid_1']['table'] = 'node';
$handler->display->display_options['fields']['nid_1']['field'] = 'nid';
$handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid_1']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['nid_1']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['nid_1']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['nid_1']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['nid_1']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['nid_1']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['nid_1']['alter']['trim'] = 0;
$handler->display->display_options['fields']['nid_1']['alter']['html'] = 0;
$handler->display->display_options['fields']['nid_1']['element_label_colon'] = 1;
$handler->display->display_options['fields']['nid_1']['element_default_classes'] = 1;
$handler->display->display_options['fields']['nid_1']['hide_empty'] = 0;
$handler->display->display_options['fields']['nid_1']['empty_zero'] = 0;
$handler->display->display_options['fields']['nid_1']['link_to_node'] = 1;
/* Field: Content revision: Log message */
$handler->display->display_options['fields']['log']['id'] = 'log';
$handler->display->display_options['fields']['log']['table'] = 'node_revision';
$handler->display->display_options['fields']['log']['field'] = 'log';
$handler->display->display_options['fields']['log']['exclude'] = TRUE;
$handler->display->display_options['fields']['log']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['log']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['log']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['log']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['log']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['log']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['log']['alter']['trim'] = 0;
$handler->display->display_options['fields']['log']['alter']['html'] = 0;
$handler->display->display_options['fields']['log']['element_label_colon'] = 1;
$handler->display->display_options['fields']['log']['element_default_classes'] = 1;
$handler->display->display_options['fields']['log']['hide_empty'] = 0;
$handler->display->display_options['fields']['log']['empty_zero'] = 0;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['title']['alter']['trim'] = 0;
$handler->display->display_options['fields']['title']['alter']['html'] = 0;
$handler->display->display_options['fields']['title']['hide_empty'] = 0;
$handler->display->display_options['fields']['title']['empty_zero'] = 0;
$handler->display->display_options['fields']['title']['link_to_node'] = 1;
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['type']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['type']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['type']['alter']['trim'] = 0;
$handler->display->display_options['fields']['type']['alter']['html'] = 0;
$handler->display->display_options['fields']['type']['hide_empty'] = 0;
$handler->display->display_options['fields']['type']['empty_zero'] = 0;
$handler->display->display_options['fields']['type']['link_to_node'] = 0;
$handler->display->display_options['fields']['type']['machine_name'] = 0;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'Revised by';
$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
$handler->display->display_options['fields']['name']['alter']['html'] = 0;
$handler->display->display_options['fields']['name']['element_label_colon'] = 1;
$handler->display->display_options['fields']['name']['element_default_classes'] = 1;
$handler->display->display_options['fields']['name']['hide_empty'] = 0;
$handler->display->display_options['fields']['name']['empty_zero'] = 0;
$handler->display->display_options['fields']['name']['link_to_user'] = 1;
$handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
/* Field: Content: Updated date */
$handler->display->display_options['fields']['changed']['id'] = 'changed';
$handler->display->display_options['fields']['changed']['table'] = 'node';
$handler->display->display_options['fields']['changed']['field'] = 'changed';
$handler->display->display_options['fields']['changed']['label'] = 'Last updated';
$handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 0;
$handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 0;
$handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
$handler->display->display_options['fields']['changed']['alter']['html'] = 0;
$handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
$handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
$handler->display->display_options['fields']['changed']['hide_empty'] = 0;
$handler->display->display_options['fields']['changed']['empty_zero'] = 0;
$handler->display->display_options['fields']['changed']['date_format'] = 'time ago';
/* Field: State Flow States: state flow events form */
$handler->display->display_options['fields']['state_flow_events_form']['id'] = 'state_flow_events_form';
$handler->display->display_options['fields']['state_flow_events_form']['table'] = 'state_flow_states';
$handler->display->display_options['fields']['state_flow_events_form']['field'] = 'state_flow_events_form';
$handler->display->display_options['fields']['state_flow_events_form']['label'] = 'Moderate';
$handler->display->display_options['fields']['state_flow_events_form']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['external'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['trim_whitespace'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['more_link'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['trim'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['alter']['html'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['element_label_colon'] = 1;
$handler->display->display_options['fields']['state_flow_events_form']['element_default_classes'] = 1;
$handler->display->display_options['fields']['state_flow_events_form']['hide_empty'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['empty_zero'] = 0;
$handler->display->display_options['fields']['state_flow_events_form']['hide_alter_empty'] = 1;
$handler->display->display_options['fields']['state_flow_events_form']['show_only_for_active_revision_ids'] = 1;
/* Sort criterion: Content: Updated date */
$handler->display->display_options['sorts']['changed']['id'] = 'changed';
$handler->display->display_options['sorts']['changed']['table'] = 'node';
$handler->display->display_options['sorts']['changed']['field'] = 'changed';
$handler->display->display_options['sorts']['changed']['order'] = 'DESC';
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
/* Filter criterion: Content: Title */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'node';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['operator'] = 'contains';
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
$handler->display->display_options['filters']['title']['expose']['use_operator'] = FALSE;
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember'] = 1;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['exposed'] = TRUE;
$handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type']['expose']['use_operator'] = FALSE;
$handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
$handler->display->display_options['filters']['type']['expose']['remember'] = 1;
$handler->display->display_options['filters']['type']['expose']['reduce'] = 0;
/* Filter criterion: Broken/missing handler */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  'all' => 'all',
  'draft' => 'draft',
  'needs_review' => 'needs_review',
  'published' => 'published',
);
$handler->display->display_options['filters']['state']['exposed'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['label'] = 'State';
$handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
$handler->display->display_options['filters']['state']['expose']['remember'] = 1;
/* Filter criterion: Broken/missing handler */
$handler->display->display_options['filters']['current']['id'] = 'current';
$handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['current']['field'] = 'current';

/* Display: Needs Review Page */
$handler = $view->new_display('page', 'Needs Review Page', 'needs_review_page');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Needs Review';
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'use workbench_moderation needs review tab';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = FALSE;
$handler->display->display_options['empty']['area']['content'] = 'This list displays content in the "Needs Review" state that you can moderate. Currently there is no such content.';
$handler->display->display_options['empty']['area']['format'] = 'plain_text';
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Content: Title */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'node';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['operator'] = 'contains';
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
$handler->display->display_options['filters']['title']['expose']['use_operator'] = FALSE;
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember'] = 1;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['exposed'] = TRUE;
$handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type']['expose']['use_operator'] = FALSE;
$handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
$handler->display->display_options['filters']['type']['expose']['remember'] = 1;
$handler->display->display_options['filters']['type']['expose']['reduce'] = 0;
/* Filter criterion: State Flow States: Active */
$handler->display->display_options['filters']['active']['id'] = 'active';
$handler->display->display_options['filters']['active']['table'] = 'state_flow_states';
$handler->display->display_options['filters']['active']['field'] = 'active';
$handler->display->display_options['filters']['active']['value'] = '1';
/* Filter criterion: State Flow States: Revision current state */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'state_flow_states';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = 'needs_review';
$handler->display->display_options['filters']['state']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['state']['expose']['label'] = 'Revision current state';
$handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
$handler->display->display_options['filters']['state']['expose']['required'] = 0;
$handler->display->display_options['path'] = 'admin/workbench/needs-review';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Needs Review';
$handler->display->display_options['menu']['weight'] = '99';

/* Display: Drafts Page */
$handler = $view->new_display('page', 'Drafts Page', 'drafts_page');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'My Drafts';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = FALSE;
$handler->display->display_options['empty']['area']['content'] = 'This list displays content you have created that is not published. Currently there is no such content.';
$handler->display->display_options['empty']['area']['format'] = 'plain_text';
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
/* Filter criterion: Broken/missing handler */
$handler->display->display_options['filters']['current']['id'] = 'current';
$handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['current']['field'] = 'current';
$handler->display->display_options['filters']['current']['value'] = '1';
/* Filter criterion: Content: Title */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'node';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['operator'] = 'contains';
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
$handler->display->display_options['filters']['title']['expose']['use_operator'] = FALSE;
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember'] = 1;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['exposed'] = TRUE;
$handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type']['expose']['use_operator'] = FALSE;
$handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
$handler->display->display_options['filters']['type']['expose']['remember'] = 1;
$handler->display->display_options['filters']['type']['expose']['reduce'] = 0;
/* Filter criterion: Broken/missing handler */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  'draft' => 'draft',
  'needs_review' => 'needs_review',
);
$handler->display->display_options['filters']['state']['exposed'] = TRUE;
$handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['label'] = 'State';
$handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
$handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
$handler->display->display_options['filters']['state']['expose']['remember'] = 1;
$handler->display->display_options['path'] = 'admin/workbench/drafts';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'My Drafts';
$handler->display->display_options['menu']['weight'] = '98';
