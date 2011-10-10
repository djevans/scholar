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
   * @param IslandoraSolrQueryProcessor $solrQueryProcessor
   * @param string $title
   * @param string $output 
   *
  function displayResults(IslandoraSolrQueryProcessor $solrQueryProcessor, $title = "Search Results", $output = '') {
    
  }*/
}