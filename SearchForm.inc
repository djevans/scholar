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
            '#type' => 'select',
            '#options' => array(
                $title => t('Title'),
                $author => t('Author'),
                $text => t('Text'),
            ),
        ),
        'sort' => array(
            '#type' => 'select',
            '#options' => array(
                NULL => 'Order By...',
                'relevance' => t('Relevance'),
                'date' => t('Date'),
            ),
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
    $url = preg_replace('/%/', $field, MENU_SCHOLAR_SEARCH, 1);
    $url = preg_replace('/%/', $sort, $url, 1);
    $url = preg_replace('/%/', $search, $url, 1);
    $form_state['redirect'] = $url;
}

function foo() {
  global $queryClass;
  islandora_solr_search_init();
  // Build and execute Apache Solr query
  $queryResult = $queryClass->buildAndExecuteQuery($query, $fq, $dismax);

  // Get the preferred display profile
  // Order: First choice is what's in the ?profile query var
  //        Second choice is the primary display profile
  //        Third choice is the default IslandoraSolrResults
  $islandora_solr_primary_display = variable_get('islandora_solr_primary_display', 'default');
  $islandora_solr_selected_display = isset($_GET['solr_profile']) ? $_GET['solr_profile'] : null;
  $primary_profiles = module_invoke_all("islandora_solr_primary_display");
  $secondary_profiles = module_invoke_all("islandora_solr_secondary_display");

  // TODO: Also filter secondary displays against those checked in the configuration options.
  if (isset($secondary_profiles[$islandora_solr_selected_display])) {
    $profile = $secondary_profiles[$islandora_solr_selected_display];
  }
  elseif (isset($primary_profiles[$islandora_solr_primary_display])) {
    $profile = $primary_profiles[$islandora_solr_primary_display];
  }
  else {
    drupal_set_message("There is an error in the solr search configuration: the display profile is not found.", 'error');
    $profile = $primary_profiles['default'];
  }

  // Include the file for the display profile
  require_once(drupal_get_path('module', $profile['module']) . '/' . $profile['file']);

  // Set display class and function vars
  $solrClass = $profile['class'];
  $solrFunction = $profile['function'];

  $nope = false;

  if (class_exists($solrClass)) {
    $implementation = new $solrClass();
  }
  else {
    $nope = true;
  }

  if (!$nope && method_exists($implementation, $solrFunction)) {
    $output = $implementation->$solrFunction($queryClass);
  }
  else {
    $nope = true;
  }

  if ($nope) {
    module_load_include('inc', 'islandora_solr_search', 'IslandoraSolrResults');
    $resultsClass = new IslandoraSolrResults();
    $output = $resultsClass->displayResults($queryClass);
  }

  if (variable_get('islandora_solr_search_debug_mode', 0)) { // debug dump
    drupal_set_message('Params: <br/><pre>' . print_r($queryClass->solrParams, true) . '</pre>', 'status');
  }

  return $output;
}