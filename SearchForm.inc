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
  drupal_add_css(drupal_get_path('module', 'scholar') . '/css/Search.css');
  module_load_include('inc', 'islandora_solr_search', 'includes/common');
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
        '#options' => islandora_build_substitution_list(variable_get('islandora_solr_searchterms', <<<EOT
dc.title ~ Title
coh_search_abstract ~ Abstract
coh_search_author_identifier ~ Author Identifier
coh_search_author ~ Author
coh_search_author_affiliation ~ Author Affiliation
coh_search_book_title ~ Book Title
coh_search_collection_series_title ~ Collection/Series Title
coh_search_group_author ~ Group Author
coh_search_editor ~ Editor
coh_search_grant_number ~ Grant Number
coh_search_funding_agency ~ Funding Agency
coh_search_isbn ~ ISBN
coh_search_issn ~ ISSN
coh_search_full_journal_title ~ Full Journal Title
coh_search_language ~ Language
coh_search_mesh_terms ~ MeSH Terms
coh_search_publication_type ~ Publication Type
coh_search_chemical_or_substance_name ~ Chemical or Substance Name
coh_search_secondary_source_id ~ Secondary Source ID
coh_search_title ~ Title
coh_search_doi ~ DOI
coh_search_conference ~ Conference
coh_search_keywords ~ Keywords
coh_search_book_group_authors ~ Book Group Authors
coh_search_times_cited ~ Times Cited
coh_search_year_published ~ Year published
coh_search_tumor_model ~ Tumour Model
coh_search_biological_pathway ~ Biological Pathway
coh_search_status ~ Status
coh_search_osr_id_number ~ OSR ID number
coh_search_cancer_center_program_code ~ Cancer Center Program Code
coh_search_cancer_center_membership_level ~ Cancer Center Membership Level
coh_search_dept_id ~ Dept ID
coh_search_dept_name ~ Dept Name
coh_search_division_id ~ Division ID
coh_search_division_name ~ Division Name
coh_search_cores ~ Cores
EOT
        ))
      ),
      'search' => array(
        '#title' => t('Search'),
        '#type' => 'textfield',
        '#default_value' => isset($values['terms'][$i]['search']) ? $values['terms'][$i]['search'] : NULL,
      ),
      'hidden_submit' => array(// Used for when the user presses enter on the search field.
        '#type' => 'submit',
        '#value' => t('Search'),
        '#attributes' => array('style' => 'visibility:hidden;position:fixed;top:-1000px;right:-1000px;')
      ),
      'add' => array(
        '#type' => 'button',
        '#value' => '+',
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
        '#value' => '-',
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
