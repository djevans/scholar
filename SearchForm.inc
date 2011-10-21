<?php

// $Id$

/**
 * @file
 *
 * Contains the hooks for rendering and processing the Quick Search form.
 */

/**
 * Builds a drupal form for launching a quick search.
 * 
 * @param array $form_state 
 * 
 * @return array
 */
function scholar_search_form(array &$form_state) {
  $title = variable_get(VAR_SCHOLAR_SEARCH_FIELD_TITLE, 'title');
  $author = variable_get(VAR_SCHOLAR_SEARCH_FIELD_TITLE, 'author');
  $text = variable_get(VAR_SCHOLAR_SEARCH_FIELD_TITLE, 'text');
  return array(
    'field' => array(
      '#title' => t('Field'),
      '#type' => 'select',
      '#options' => array(
        $title => t('Title'),
        $author => t('Author'),
        $text => t('Text'),
      ),
    ),
    'sort' => array(
      '#title' => t('Sort By'),
      '#type' => 'select',
      '#options' => array(
        'relevance' => t('Relevance'),
        'title' => t('Title'),
        'date' => t('Date'),
      ),
      '#value' => 'relevance'
    ),
    'search' => array(
      '#type' => 'textfield',
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => 'Search'
    )
  );
}

/**
 * Submit hook for the quick search form.
 * 
 * @param array $form
 * @param array $form_state 
 */
function scholar_search_form_submit(array $form, array &$form_state) {
  $field = $form_state['values']['field'];
  $sort = ($form_state['values']['sort'] != '') ? $form_state['values']['sort'] : 'relevance';
  $search = $form_state['values']['search'];
  $fields = array(
    'title' => 'dc.title',
    'author' => 'dc.contributor',
    'text' => 'text'
  );
  $field = $fields[$field]; // Remap Field to query friendly one.
  $query = !empty($search) ? $field . ':' . $search : '*';
  $form_state['redirect'] = 'islandora/solr/search/' . $query . '/';
}