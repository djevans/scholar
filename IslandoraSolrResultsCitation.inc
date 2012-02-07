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
    $sort = $_SESSION['scholar']['search']['sort'];
    $order = $_SESSION['scholar']['search']['order'];
    if (!empty($_SESSION['scholar']['search']['sort'])) {
      $query_processor->solrParams['fl'] = 'PID,mod_fullxml_store';
      $query_processor->solrParams['sort'] = $sort . ' ' . $order;
      $query_processor->executeQuery();
    }
    $total = (int) $query_processor->solrResult->response->numFound;
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
    module_load_include('inc', 'csl', 'CSL');
    $style = citeproc_default_style();
    foreach ($results->response->docs as $doc) {
      $output .= theme(THEME_SCHOLAR_SEARCH_ITEM, $doc->PID, $style);
    }
    return $output;
  }

}

function template_preprocess_scholar_search_alt_item(array &$vars)  {
  $s_doc =& $vars['solr_doc'];
  $pid = $s_doc->PID;
  $title = $s_doc->mods_title_ms;
  if (is_array($title)) {$title = $title[0];}
  
  $vars['title'] = l($title, 'fedora/repository/' . htmlspecialchars($pid, ENT_QUOTES, 'utf-8'));
  
  $vars['citation'] = scholar_citation_from_solr_doc($s_doc, $vars['style']);
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
    
    $style = $variables['style'];
    $cache_id = "citation_{$pid}";
    $cached_raw = cache_get($cache_id);
    
    $bibliography = NULL;
    if (!empty($cached_raw)) {
      $bibliography = citeproc_bibliography_from_raw_array($style, $cached_raw->data);
    }
    else {
      $mods = $item->get_datastream_dissemination('MODS');
      $mods = trim($mods);
      if (!empty($mods)) {
        $doc = new DOMDocument();
        $doc->loadXML($mods);
        $variables['coins'] = scholar_convert_mods_to_coins($doc); // djevans
        $bibliography = citeproc_bibliography_from_mods($style, $doc, $cache_id);
      }
    }
    $variables['citation'] = $bibliography->render();
  }
}

function scholar_search_results_form(array &$form_state, IslandoraSolrQueryProcessor $query_processor) {
  citation_exporter_include_download_redirect();
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

  module_load_include('inc', 'csl', 'CSL');
  $style = citeproc_default_style();
  $pids = array();
  foreach ($results->response->docs as $doc) {
    $pid = $doc->PID;
    $result = '';
      $pids[] = $pid;
      $result = theme(THEME_SCHOLAR_SEARCH_ITEM, $pid, $style);
      $table['rows'][] = array(
        '#pid' => $pid,
        'result' => array('#value' => $result),
      );
  }
  $checkboxes = array_fill_keys($pids, '');
  $table['selections'] = array(
    '#type' => 'checkboxes',
    '#options' => $checkboxes,
  );
  $form_state['storage']['query'] = $query_processor;
  return array(
    'controls' => array(
      '#type' => 'markup',
      '#prefix' => '<div class="scholar-export-controls">',
      '#suffix' => '</div>',
      'export' => array(
        '#value' => t('Export To File'),
        '#prefix' => '<h4>',
        '#suffix' => '</h4>'
      ),
      'format' => array(
        '#type' => 'select',
        '#length' => 50,
        '#options' => array(
          'RIS' => 'RIS (EndNote format)',
          'RTF' => 'RTF (word processor format)',
          'PDF' => 'PDF',
          'Tagged' => 'EndNote (Tagged)',
          'BibTEX' => 'BibTEX',
          'MARCXML' => 'MARCXML',
        )
      ),
      'style' => array(
        '#type' => 'select',
        '#options' => CSL::GetNames()
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
  // @todo prevent submission with more then.
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
  module_load_include('inc', 'islandora_bibliography', 'Bibliography');
  $action = $form_state['clicked_button']['#save'];
  if ($action == 'all') {
    $pids = _scholar_search_get_all_pids_from_query($form_state);
  }
  else {
    $pids = $form_state['values']['table']['selections'];
    $pids = array_filter($pids);
    $pids = array_keys($pids);
  }
  $count = Bibliography::AddCitations($pids);
  $form_state['storage'] = NULL;
  drupal_set_message(t('Added %num Citation(s)', array('%num' => $count)));
}

function scholar_search_results_form_export(array $form, array &$form_state) {
  $action = $form_state['clicked_button']['#export'];
  if ($action == 'all') {
    $pids = _scholar_search_get_all_pids_from_query($form_state);
  }
  else {
    $selections = array_filter($form_state['values']['table']['selections']);
    $pids = array_keys($selections);
  }
  module_load_include('inc', 'citation_exporter', 'Batch');
  citation_exporter_batch_export($pids, $form_state['values']['style'], $form_state['values']['format']);
  batch_process();
  unset($form_state['storage']);
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

/**
 * Convert an object's MODS datastream to COINS metadata.
 *
 * @param DOMDocument $doc
 *  A DOMDocument containing the object's MODS metadata stream.
 * @return string
 *  A URL-encoded string containing CoiNS metadata.
 */
function scholar_convert_mods_to_coins($doc) {
  
  $path = drupal_get_path('module','scholar');
  
  $xsl = new DOMDocument();
  $xsl->load($path .'/xsl/coins.xsl');
  
  $xsltproc = new XSLTProcessor();
  $xsltproc->importStylesheet($xsl);
  
  $sid = variable_get('biblio_openurl_sid','biblio:'. variable_get('site_name','Drupal'));
  $xsltproc->setParameter('','referer',$sid);
  
  $outputString = $xsltproc->transformToXML($doc); 

  $pairs = explode('&',trim($outputString));
  $new_pairs = array();
  foreach ($pairs as $pair) {
    list($key,$value) = explode('=',$pair);
    $new_pairs[] = $key .'='. urlencode($value);
  }
  return implode('&amp;',$new_pairs);
  
}