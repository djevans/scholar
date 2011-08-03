<?php

// $Id$

/**
 * @file
 *
 * Implements hooks and callbacks for the admin section.
 */

/**
 * Build the Admin settings form.
 * 
 * @param array $form_state 
 * 
 * @return array
 */
function scholar_admin_settings(array &$form_state) {
  $form = array();
  $form[VAR_SCHOLAR_SEARCH_FIELD_TITLE] = array(
    '#type' => 'textfield',
    '#title' => t('Title Search Field'),
    '#description' => t('The SOLR search field used for title.'),
    '#default_value' => variable_get(VAR_SCHOLAR_SEARCH_FIELD_TITLE, 'title'),
    '#required' => TRUE,
  );
  $form[VAR_SCHOLAR_SEARCH_FIELD_AUTHOR] = array(
    '#type' => 'textfield',
    '#title' => t('Author Search Field'),
    '#description' => t('The SOLR search field used for author.'),
    '#default_value' => variable_get(VAR_SCHOLAR_SEARCH_FIELD_AUTHOR, 'author'),
    '#required' => TRUE,
  );
  $form[VAR_SCHOLAR_SEARCH_FIELD_TEXT] = array(
    '#type' => 'textfield',
    '#title' => t('Text Search Field'),
    '#description' => t('The SOLR search field used for text.'),
    '#default_value' => variable_get(VAR_SCHOLAR_SEARCH_FIELD_TEXT, 'text'),
    '#required' => TRUE,
  );
  $form[VAR_SCHOLAR_SEARCH_FIELD_USER] = array(
    '#type' => 'textfield',
    '#title' => t('User Search Field'),
    '#description' => t('The SOLR search field used for user.'),
    '#default_value' => variable_get(VAR_SCHOLAR_SEARCH_FIELD_USER, 'user'),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}