<?php

/**
 * @file
 *
 */
module_load_include('inc', 'islandora_solr_search', 'IslandoraSolrResults');

/**
 * Extention of IslandoraSolrResults for templating purposes.
 * This overrides the displayResults function to provide an alternate display type.
 */
class IslandoraSolrResultsCitation extends IslandoraSolrResults {

  /**
   * Overrides parent function.
   * 
   * @param IslandoraSolrQueryProcessor $query_processor
   * @param string $title
   * @param string $output 
   */
  function displayResults(IslandoraSolrQueryProcessor $query_processor, $title = "Search Results", $output = '') {
    module_load_include('inc', 'scholar', 'SearchForm');
    drupal_add_css(drupal_get_path('module', 'scholar') . '/css/Search.css');
    $solr_result = $query_processor->solrResult;
    $total = (int) $solr_result->response->numFound;
    $end = min(($query_processor->solrLimit + $query_processor->solrStart), $total);
    $output = '<h4>Advanced Search</h4>';
    $output .= drupal_get_form('scholar_search_form');
// Check for empty resultset
    if ($total === 0) {
      $output .= "<h2>Search Results</h2>";
      $output .= "<div>Sorry, but your search returned no results.</div>";
      return $output;
    }
// Initialize drupal-style pager
    islandora_solr_search_pager_init($total, $query_processor->solrLimit);
    //$output .= '<h2>' . $title . '</h2>';
    //$output .= '<div id="islandora_solr_result_count">(' . ($query_processor->solrStart + 1) . ' - ' . $end . ' of ' . $total . ')</div>';
    $output .= '<div class="content">';
    $output .= drupal_get_form('scholar_search_results_form', $query_processor->solrResult); //$this->printResults($query_processor->solrResult);
// Render Drupal pager (bottom of search results)
    $output .= theme('pager', null, $query_processor->solrLimit, 0, null, 5);
    $output .= "</div>"; // class = "content"
    return $output;
  }

  /**
   * Function: printResults
   *
   * Description: translates a solr query result into a basic in-browser search result.
   *
   * @param Apache_Solr_Object $results
   */
  function printResults($results) {
    module_load_include('inc', 'fedora_repository', 'api/fedora_item');
    if (empty($results)) {
      return "no results";
    }
    $output = '';
    $record_start = $results->response->start;
    $limit_results = variable_get('islandora_solr_search_limit_result_fields', 0);
    $style_filename = drupal_get_path('module', 'citeproc') . '/data/apa.csl';
    $style = citeproc_style($style_filename);
    foreach ($results->response->docs as $doc) {
      $pid = $doc->PID;
      $item = new Fedora_Item($pid);
      if ($item->exists() && isset($item->datastreams['MODS'])) {
        $output .= theme(THEME_SCHOLAR_SEARCH_ITEM, $pid, $style);
      }
    }
    return $output;
  }

}

/**
 *
 * @param array $variables 
 */
function template_preprocess_scholar_search_item(array &$variables) {
  module_load_include('inc', 'fedora_repository', 'api/fedora_item');
  $pid = $variables['pid'];
  $item = new Fedora_Item($pid);
  if ($item->exists() && isset($item->datastreams['MODS'])) {
    $title = $item->objectProfile->objLabel;
    $variables['title'] = l($title, 'fedora/repository/' . htmlspecialchars($pid, ENT_QUOTES, 'utf-8'));
    $mods = $item->get_datastream_dissemination('MODS');
    $mods = trim($mods);
    if (!empty($mods)) {
      $doc = new DOMDocument();
      $doc->loadXML($mods);
      $bibliography = citeproc_bibliography_from_mods($variables['style'], $doc);
      $variables['citation'] = $bibliography->render();
    }
  }
}

function scholar_search_results_form(array &$form_state, Apache_Solr_Response $results) {
  module_load_include('inc', 'fedora_repository', 'api/fedora_item');
  $table = array(
    '#header' => array(theme('table_select_header_cell'), t('Search Results')),
    '#theme' => 'scholar_search_results_table',
    '#tree' => TRUE,
  );
  $record_start = $results->response->start;
  $limit_results = variable_get('islandora_solr_search_limit_result_fields', 0);
  $style_filename = drupal_get_path('module', 'citeproc') . '/data/apa.csl';
  $style = citeproc_style($style_filename);
  $pids = array();
  foreach ($results->response->docs as $doc) {
    $pid = $doc->PID;
    $result = '';
    $item = new Fedora_Item($pid);
    if ($item->exists() && isset($item->datastreams['MODS'])) {
      $pids[] = $pid;
      $result = theme(THEME_SCHOLAR_SEARCH_ITEM, $pid, $style);
      $table['rows'][] = array(
        '#pid' => $pid,
        'result' => array('#value' => $result),
      );
    }
  }
  $checkboxes = array_fill_keys($pids, '');
  $table['selections'] = array(
    '#type' => 'checkboxes',
    '#options' => $checkboxes,
  );
  /**
   * Export
   *   -Selected
   *   -All
   * 
   * Export to File (only no rendering on screen)
   *   -File Format (RIS, PDF, RTF)
   *
   * Citation Style (Only shows for PDF RTF) ?
   *   - APA, NIH, NLM, Annotated
   * 
   *  -- Export to File-----------
   *  |
   *  | File Format [RIS]   Citation Style [APA]  "Selected Results" "All Results"
   * 
   * Save to Bibliography
   *   -Selected
   *   -All
   */
  return array(
    'export' => array(
      '#value' => t('Export To File'),
      '#prefix' => '<h4>',
      '#suffix' => '</h4>'
    ),
    'format' => array(
      //'#title' => t('File Format'),
      '#type' => 'select',
      '#length' => 50,
      '#options' => array(
        'RIS' => 'RIS',
        'RTF' => 'RTF',
        'PDF' => 'PDF',
      )
    ),
    'style' => array(
      //'#title' => t('Citation Style'),
      '#type' => 'select',
      '#options' => array(
        'apa.csl' => 'APA',
        'annotated.csl' => 'Annotated',
        'nih.csl' => 'NIH',
        'nlm.csl' => 'NLM',
      )
    ),
    'export all' => array(
      '#type' => 'submit',
      '#action' => 'export',
      '#value' => t('Export All Results'),
    ),
    'export selected' => array(
      '#type' => 'submit',
      '#action' => 'export',
      '#value' => t('Export Selected'),
    ),
    'save' => array(
      '#value' => t('Save to Bibliography'),
      '#prefix' => '<h4>',
      '#suffix' => '</h4>'
    ),
    'save all' => array(
      '#type' => 'submit',
      '#action' => 'export',
      '#value' => t('Save All Results'),
    ),
    'save selected' => array(
      '#type' => 'submit',
      '#action' => 'export',
      '#value' => t('Save Selected'),
    ),
    'table' => $table,
  );
  return array(
    'table' => $table
  );
  /* module_load_include('inc', 'fedora_repository', 'api/fedora_item');
    if (empty($results)) {
    return "no results";
    }
    $output = '';
    $record_start = $results->response->start;
    $limit_results = variable_get('islandora_solr_search_limit_result_fields', 0);
    $style_filename = drupal_get_path('module', 'citeproc') . '/data/apa.csl';
    $style = citeproc_style($style_filename);
    foreach ($results->response->docs as $doc) {
    $pid = $doc->PID;
    $item = new Fedora_Item($pid);
    if ($item->exists() && isset($item->datastreams['MODS'])) {
    $output .= theme(THEME_SCHOLAR_SEARCH_ITEM, $pid, $style);
    }
    }
    return $output;
   */
}

function scholar_search_results_form_submit(array &$form_state, Apache_Solr_Response $results) {
  
}

/**
 * Theme's a form table for this module.
 *
 * @param array $element
 *   A Drupal Form Element.
 *
 * @return sting
 *   HTML that renders a table of settings for datastreams.
 */
function theme_scholar_search_results_table(array $element) {
  $rows = array();
  foreach (element_children($element['rows']) as $child) {
    $setting = $element['rows'][$child];
    $pid = $setting['#pid'];
    $fields = array(
      drupal_render($element['selections'][$pid]) // First field is a checkbox
    );
    foreach (element_children($setting) as $property) {
      $field = $setting[$property];
      $fields[] = drupal_render($field);
    }
    $rows[] = array(
      'data' => $fields,
      'class' => isset($setting['#attributes']['class']) ? $setting['#attributes']['class'] : NULL
    );
  }
  $attributes = isset($element['#id']) ? array('id' => $element['#id']) : NULL;
  return '<div class="scholar-search-results">' . theme_table($element['#header'], $rows, $attributes) . '</div>';
}