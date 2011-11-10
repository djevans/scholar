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
          //'#value' => 'dc.text',
          '#options' => $search_fields
        ),
        'search' => array(
          '#type' => 'textfield',
        )
      ),
    /* 1 => array(// Defaults to title
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
      ), */
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
  //$field = $form_state['values']['field'];
  //$search = $form_state['values']['search'];
  $query = !empty($search) ? $field . ':' . $search : '*'; // Empty return all results. 
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