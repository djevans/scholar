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
  drupal_add_js(drupal_get_path('module', 'scholar') . '/js/Ahah.js');
  $num_terms = 1;
  if (isset($form_state['values'])) {
    $values = $form_state['values'];
    $num_terms = isset($form_state['num_terms']) ? $form_state['num_terms'] : $num_terms;
  }
  else if (isset($_SESSION['scholar']['search']['values'])) {
    /**
     * Handles the changing of URL from the initial search page to the actual search page.
     */
    $values = $_SESSION['scholar']['search']['values'];
    $num_terms = count($values['terms']);
    unset($_SESSION['scholar']['search']['values']); // Forget this for the next page visit.
  }
  $terms = array(
    '#prefix' => '<div id="scholar-search-terms">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );
  for ($i = 0; $i < $num_terms; $i++) {
    $term = array(
      '#tree' => TRUE,
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      'field' => array(
        '#title' => t('Field'),
        '#type' => 'select',
        '#default_value' => isset($values['terms'][$i]['field']) ? $values['terms'][$i]['field'] : 'coh_search_title',
        '#options' => array(
          'coh_search_abstract' => t('Abstract'),
          'coh_search_author_identifier' => t('Author Identifier'),
          'coh_search_author' => t('Author'),
          'coh_search_author_affiliation' => t('Author Affiliation'),
          'coh_search_book_title' => t('Book Title'),
          'coh_search_collection_series_title' => t('Collection/Series Title'),
          'coh_search_group_author' => t('Group Author'),
          'coh_search_editor' => t('Editor'),
          'coh_search_grant_number' => t('Grant Number'),
          'coh_search_funding_agency' => t('Funding Agency'),
          'coh_search_isbn' => t('ISBN'),
          'coh_search_issn' => t('ISSN'),
          'coh_search_full_journal_title' => t('Full Journal Title'),
          'coh_search_language' => t('Language'),
          'coh_search_mesh_terms' => t('MeSH Terms'),
          'coh_search_publication_type' => t('Publication Type'),
          'coh_search_chemical_or_substance_name' => t('Chemical or Substance Name'),
          'coh_search_secondary_source_id' => t('Secondary Source ID'),
          'coh_search_title' => t('Title'),
          'coh_search_doi' => t('DOI'),
          'coh_search_conference' => t('Conference'),
          'coh_search_keywords' => t('Keywords'),
          'coh_search_book_group_authors' => t('Book Group Authors'),
          'coh_search_times_cited' => t('Times Cited'), // Hack this one...
          'coh_search_year_published' => t('Year published'),
          'coh_search_tumor_model' => t('Tumour Model'),
          'coh_search_biological_pathway' => t('Biological Pathway'),
          'coh_search_status' => t('Status'),
          'coh_search_osr_id_number' => t('OSR ID number'),
          'coh_search_cancer_center_program_code' => t('Cancer Center Program Code'),
          'coh_search_cancer_center_membership_level' => t('Cancer Center Membership Level'),
          'coh_search_dept_id' => t('Dept ID'),
          'coh_search_dept_name' => t('Dept Name'),
          'coh_search_division_id' => t('Division ID'),
          'coh_search_division_name' => t('Division Name'),
          'coh_search_cores' => t('Cores'),
        //'dc.text' => t('Text'),
        )
      ),
      'search' => array(
        '#title' => t('Search'),
        '#type' => 'textfield',
        '#default_value' => isset($values['terms'][$i]['search']) ? $values['terms'][$i]['search'] : NULL,
      ),
      'hidden_submit' => array(// Used for when the user presses enter on the search field.
        '#type' => 'submit',
        '#value' => 'Search',
        '#attributes' => array('style' => 'visibility:hidden;position:fixed;top:-1000px;right:-1000px;')
      ),
      'add' => array(
        '#type' => 'button',
        '#value' => 'Add Field',
        '#ahah' => array(
          'path' => MENU_SCHOLAR_ADVANCED_SEARCH_ADD_FIELD,
          'wrapper' => 'scholar-search-terms',
          'method' => 'replace',
          'effect' => 'fade'
        )
      ),
    );
    if ($i > 0) {
      $term['remove'] = array(
        '#type' => 'button',
        '#field' => $i,
        '#value' => 'Remove Field',
        '#name' => 'remove-field-' . $i,
        '#ahah' => array(
          'path' => MENU_SCHOLAR_ADVANCED_SEARCH_REMOVE_FIELD,
          'wrapper' => 'scholar-search-terms',
          'method' => 'replace',
          'effect' => 'fade'
        )
      );
    }
    $terms[] = $term;
  }
  return array(
    'terms' => $terms,
    'controls' => array(
      '#type' => 'markup',
      '#prefix' => '<div class="scholar-search-controls">',
      '#suffix' => '</div>',
      'sort' => array(
        '#title' => t('Sort By'),
        '#type' => 'select',
        '#default_value' => isset($values['sort']) ? $values['sort'] : NULL,
        '#options' => array(
          NULL => t('Relevance'),
          'coh_sort_title' => t('Title'),
          'coh_sort_date' => t('Date Added'),
        ),
      ),
      'order' => array(
        '#title' => t('Order'),
        '#type' => 'select',
        '#default_value' => isset($values['order']) ? $values['order'] : 'asc',
        '#options' => array(
          'asc' => t('Ascending'),
          'desc' => t('Descending'),
        ),
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
  $_SESSION['scholar']['search']['values'] = $form_state['values'];
  $_SESSION['scholar']['search']['sort'] = $form_state['values']['sort'];
  $_SESSION['scholar']['search']['order'] = $form_state['values']['order'];
  $query = scholar_search_form_build_query($form_state);
  $form_state['redirect'] = 'islandora/solr/search/' . urlencode($query) . '/'; // Redirect to the search.
  //coh_search_title %253A %2528 cancer %2529
}

/**
 *
 * @param array $form_state 
 */
function scholar_search_form_build_query(array &$form_state) {
  $query = 'dc.title:*';
  $statements = array();
  foreach ($form_state['values']['terms'] as $term) {
    $field = $term['field'];
    $search = trim($term['search']);
    if (!empty($search)) {
      $statements[] = "$field:($search)";
    }
  }
  $query = !empty($statements) ? implode(' AND ', $statements) : '*'; // Empty return all results. 
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

function scholar_search_advanced_add_field() {
  module_load_include('inc', 'xml_form_elements', 'Ahah');
  list($form_id, $form_build_id, $form, $form_state) = Ahah::getFormInfo();
  $form = Ahah::processForm($form_id, $form, $form_state);
  $form_state['num_terms'] = count(element_children($form['terms'])) + 1;
  $form = Ahah::rebuildForm($form_id, $form_build_id, $form, $form_state);
  Ahah::respond($form['terms']);
}

function scholar_search_advanced_remove_field() {
  module_load_include('inc', 'xml_form_elements', 'Ahah');
  list($form_id, $form_build_id, $form, $form_state) = Ahah::getFormInfo();
  $form = Ahah::processForm($form_id, $form, $form_state);
  $field = $form_state['clicked_button']['#field'];
  array_splice($form_state['values']['terms'], $field, 1);
  $form_state['num_terms'] = count($form_state['values']['terms']);
  $form = Ahah::rebuildForm($form_id, $form_build_id, $form, $form_state);
  Ahah::respond($form['terms']);
}