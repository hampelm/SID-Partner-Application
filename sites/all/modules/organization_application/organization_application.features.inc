<?php

/**
 * Implementation of hook_node_info().
 */
function organization_application_node_info() {
  $items = array(
    'organization' => array(
      'name' => t('Organization'),
      'module' => 'features',
      'description' => t('This content type is for organizations to describe themselves.'),
      'has_title' => '1',
      'title_label' => t('Organization Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'project' => array(
      'name' => t('Project'),
      'module' => 'features',
      'description' => t('Description of each project'),
      'has_title' => '1',
      'title_label' => t('Project Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function organization_application_views_api() {
  return array(
    'api' => '2',
  );
}
