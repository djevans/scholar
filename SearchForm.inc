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
  return array(
    'field' => array(
      '#type' => 'select',
      '#options' => array(
        'title' => t('Title'),
        'author' => t('Author'),
        'text' => t('Text'),
      ),
    ),
    'sort' => array(
      '#type' => 'select',
      '#options' => array(
        'date' => t('Date'),
        'relevance' => t('Relevance'),
      ),
    ),
    'search' => array(
      '#type' => 'textfield'
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
  $form_state['redirect'] = MENU_SCHOLAR_SEARCH;
}