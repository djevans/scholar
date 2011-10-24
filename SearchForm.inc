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
  $search_fields = array(
    'dc.title' => t('Title'),
    'dc.author' => t('Author'),
    '1' => t('Publication Type'),
    '2' => t('Funding Agency'),
    '3' => t('Cancer Center Program'),
    '4' => t('Grant Number'),
    '5' => t('Publication Date'),
    '6' => t('Date Added'),
    '7' => t('Peer Reviewed'),
    'dc.text' => t('Text'),
  );
  $search_term = array(
    '#prefix' => '<div>',
    '#suffix' => '</div>',
    'field' => array(
      '#title' => t('Field'),
      '#type' => 'select',
      '#options' => $search_fields
    ),
    'search' => array(
      '#type' => 'textfield',
    )
  );
  $terms = array(
  );
  foreach ($form_state['storage']['terms'] as $term) {
    
  }
  return array(
    'terms' => array(
      '#prefix' => '<div class="scholar-search-terms">',
      '#suffix' => '</div>',
      '#tree' => TRUE,
      0 => array(// Defaults to title
        '#prefix' => '<div>',
        '#suffix' => '</div>',
        'field' => array(
          '#title' => t('Field'),
          '#type' => 'select',
          '#value' => 'dc.text',
          '#options' => $search_fields
        ),
        'search' => array(
          '#type' => 'textfield',
        )
      ),
      1 => array(// Defaults to title
        '#prefix' => '<div>',
        '#suffix' => '</div>',
        'field' => array(
          '#title' => t('Field'),
          '#type' => 'select',
          '#value' => 'dc.text',
          '#options' => $search_fields
        ),
        'search' => array(
          '#type' => 'textfield',
        )
      ),
      2 => array(// Defaults to title
        '#prefix' => '<div>',
        '#suffix' => '</div>',
        'field' => array(
          '#title' => t('Field'),
          '#type' => 'select',
          '#value' => 'dc.text',
          '#options' => $search_fields
        ),
        'search' => array(
          '#type' => 'textfield',
        )
      ),
    ),
    'hidden_submit' => array(// Used for when the user presses enter on the search field.
      '#type' => 'submit',
      '#attributes' => array('style' => 'visibility:hidden'),
      '#value' => 'Search'
    ),
    'controls' => array(
      '#type' => 'markup',
      '#prefix' => '<div class="scholar-search-controls">',
      '#suffix' => '</div>',
      'sort' => array(
        '#title' => t('Sort By'),
        '#type' => 'select',
        '#options' => array(
          '' => t('Relevance'),
          'coh_title_sort' => t('Title'),
          'coh_date_sort' => t('Date Added'),
        ),
      ),
      'order' => array(
        '#title' => t('Order'),
        '#type' => 'select',
        '#options' => array(
          'asc' => t('Ascending'),
          'desc' => t('Descending'),
        ),
      ),
      'add' => array(
        '#type' => 'button',
        '#value' => 'Add Field'
      ),
      'submit' => array(
        '#type' => 'submit',
        '#value' => 'Search'
      )
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
  scholar_search_form_store_sort_in_session($form_state);
  $query = scholar_search_form_build_query($form_state);
  $form_state['redirect'] = 'islandora/solr/search/' . $query . '/'; // Redirect to the search.
}

/**
 *
 * @param array $form_state 
 */
function scholar_search_form_build_query(array &$form_state) {
  $query = 'dc.title:*';
  foreach ($form_state['values']['terms'] as $term) {
    $field = $term['field'];
    $search = $term['search'];
  }
  $field = $form_state['values']['field'];
  $search = $form_state['values']['search'];
  !empty($search) ? $field . ':' . $search : '*'; // Empty return all results. 
  return $query;
}

/**
 *
 * @param array $form_state 
 */
function scholar_search_form_store_sort_in_session(array &$form_state) {
  $sort = $form_state['values']['sort'];
  unset($_SESSION['scholar']['search']);
  if (!empty($sort)) {
    $order = $form_state['values']['order'];
    $_SESSION['scholar']['search']['sort'] = $sort . ' ' . $order;
  }
}