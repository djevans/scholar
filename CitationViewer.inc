<?php

// $Id$

/**
 * @file
 *
 */
module_load_include('inc', 'fedora_repository', 'api/fedora_item');

/**
 * Models the display information a field books should have.
 */
class CitationViewer {

  /**
   * Object Pid.
   * 
   * @var string
   */
  protected $pid;

  /**
   * The Object.
   * 
   * @var Fedora_Item
   */
  protected $item;

  /**
   * Creates FieldBookModelViewer instance.
   * 
   * @param string $pid 
   */
  public function __construct($pid) {
    $this->pid = $pid;
    $this->item = new Fedora_Item($pid);
  }

  /**
   * Gets HTML to be rendered into the overview Panel.
   * 
   * @return string
   */
  public function getOverview() {
    return theme('scholar_overview_panel_citation', $this->pid);
  }

}

/**
 *
 * @global string $base_url
 * @param array $variables 
 */
function template_preprocess_scholar_overview_panel_citation(array &$variables) {
  module_load_include('inc', 'fedora_repository', 'api/fedora_item');
  $pid = $variables['pid'];
  $item = new Fedora_Item($pid);
  $xml = $item->get_datastream_dissemination('DC');
  $document = new DOMDocument();
  $document->loadXML($xml);
  $xpath = new DOMXPath($document);
  $result = $xpath->query('//*[local-name()="title"]');
  $title = $result->item(0);
  $result = $xpath->query('//*[local-name()="identifier"]');
  $identifier = $result->item(0);
  $variables['table'] = theme_table(array('Field', 'Value'), array(
    array('Title', $title->textContent),
    array('Identifier', $identifier->textContent))
  );
}