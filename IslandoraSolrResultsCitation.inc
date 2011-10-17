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
    $total = (int) $query_processor->solrResult->response->numFound;
    $output = '<h4>Advanced Search</h4>';
    $output .= drupal_get_form('scholar_search_form');
    if ($total === 0) {
      $output .= "<h2>Search Results</h2>";
      $output .= "<div>Sorry, but your search returned no results.</div>";
      return $output;
    }
    islandora_solr_search_pager_init($total, $query_processor->solrLimit);
    $output .= '<div class="content">';
    $output .= drupal_get_form('scholar_search_results_form', $query_processor);
    $output .= theme('pager', null, $query_processor->solrLimit, 0, null, 5);
    $output .= "</div>";
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

function scholar_search_results_form(array &$form_state, IslandoraSolrQueryProcessor $query_processor) {
  if (isset($_SESSION['bibliography']['export']['file'])) {
    $path = MENU_BIBLIOGRAPHY_EXPORT;
    drupal_set_html_head("<meta http-equiv='refresh' content='0;url=/$path'/>");
  }
  module_load_include('inc', 'fedora_repository', 'api/fedora_item');
  $results = $query_processor->solrResult;
  $total = (int) $results->response->numFound;
  $start = (int) $query_processor->solrStart + 1;
  $end = min(($query_processor->solrLimit + $query_processor->solrStart), $total);
  $title = t('Search Results (%start - %end of %total)', array('%start' => $start, '%end' => $end, '%total' => $total));
  $table = array(
    '#header' => array(theme('table_select_header_cell'), $title),
    '#theme' => 'scholar_search_results_table',
    '#tree' => TRUE,
  );
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
  $form_state['storage']['query'] = $query_processor;
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
      '#export' => 'all',
      '#value' => t('Export All Results'),
      '#submit' => array('scholar_search_results_form_export')
    ),
    'export selected' => array(
      '#type' => 'submit',
      '#action' => 'export',
      '#export' => 'selected',
      '#value' => t('Export Selected'),
      '#submit' => array('scholar_search_results_form_export')
    ),
    'save' => array(
      '#value' => t('Save to Bibliography'),
      '#prefix' => '<h4>',
      '#suffix' => '</h4>'
    ),
    'save all' => array(
      '#type' => 'submit',
      '#save' => 'all',
      '#value' => t('Save All Results'),
      '#submit' => array('scholar_search_results_form_save_to_bibliography')
    ),
    'save selected' => array(
      '#type' => 'submit',
      '#save' => 'selected',
      '#value' => t('Save Selected'),
      '#submit' => array('scholar_search_results_form_save_to_bibliography')
    ),
    'pager' => array(
      '#value' => theme('pager', null, $query_processor->solrLimit, 0, null, 5)
    ),
    'table' => $table,
  );
}

/**
 * Check to see if some thing has been selected.
 */
function scholar_search_results_form_validate(array $form, array &$form_state) {
  
}

/**
 *
 * @param array $form_state
 * @return type 
 */
function _scholar_search_get_all_pids_from_query(array &$form_state) {
  $query_processor = $form_state['storage']['query'];
  $previous_limit = $query_processor->solrLimit;
  $query_processor->solrLimit = 100000;
  $query_processor->solrParams['fl'] = 'PID';
  $query_processor->executeQuery();
  unset($query_processor->solrParams['fl']);
  $query_processor->solrLimit = $previous_limit;
  $results = $query_processor->solrResult;
  $pids = array();
  foreach ($results->response->docs as $doc) {
    $pids[] = $doc->PID;
  }
  return $pids;
}

function scholar_search_results_form_save_to_bibliography(array $form, array &$form_state) {
  $action = $form_state['clicked_button']['#save'];
  if ($action == 'all') {
    $pids = _scholar_search_get_all_pids_from_query($form_state);
  }
  else {
    $pids = $form_state['values']['table']['selections'];
    $pids = array_filter($pids);
    $pids = array_keys($pids);
  }
  $count = 0;
  foreach ($pids as $pid) {
    if (islandora_bibliography_store_citation($pid)) {
      $count++;
    }
  }
  $form_state['storage'] = NULL;
  drupal_set_message(t('Added %num Citation(s)', array('%num' => $count)));
}

function scholar_search_results_form_export(array $form, array &$form_state) {
  $action = $form_state['clicked_button']['#export'];
  $form_state['redirect'] = $_GET['q'];
  if ($action == 'all') {
    $pids = _scholar_search_get_all_pids_from_query($form_state);
    islandora_bibliography_export_citations($pids, NULL, 'RIS');
  }
  else {
    $selections = array_filter($form_state['values']['table']['selections']);
    $pids = array_keys($selections);
    islandora_bibliography_export_citations($pids, NULL, 'RIS');
  }
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