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
    $solr_result = $query_processor->solrResult;
    $total = (int) $solr_result->response->numFound;
    $end = min(($query_processor->solrLimit + $query_processor->solrStart), $total);
    // Check for empty resultset
    if ($total === 0) {
      $output = "<h2>Search Results</h2>";
      $output .= "<div>Sorry, but your search returned no results.</div>";
      return $output;
    }
    // Initialize drupal-style pager
    islandora_solr_search_pager_init($total, $query_processor->solrLimit);
    $output .= '<h2>' . $title . '</h2>';
    $output .= '<div id="islandora_solr_result_count">(' . ($query_processor->solrStart + 1) . ' - ' . $end . ' of ' . $total . ')</div>';
    $output .= '<div class="content">';
    $output .= $this->printResults($query_processor->solrResult);
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
    if (empty($results)) {
      return "no results";
    }
    $output = '';
    $record_start = $results->response->start;
    $limit_results = variable_get('islandora_solr_search_limit_result_fields', 0);
    $style_filename = drupal_get_path('module', 'citeproc') . '/data/apa.csl';
    $style = citeproc_style($style_filename);
    foreach ($results->response->docs as $doc) {
      $output .= theme(THEME_SCHOLAR_SEARCH_ITEM, $doc->PID, $style);
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