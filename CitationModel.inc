<?php

// $Id$

/**
 * @file
 *
 */
module_load_include('inc', 'fedora_repository', 'api/fedora_item');
module_load_include('inc', 'content_model_viewer', 'models/AbstractModel');

/**
 * Models the display information a field books should have.
 */
class CitationModel extends AbstractModel {

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
   * Creates CitationModel instance.
   * 
   * @param string $pid 
   */
  public function __construct($pid) {
    $this->pid = $pid;
    $this->item = new Fedora_Item($pid);
  }

  /**
   * The function required for this viewer to render correctly.
   */
  public function getInitializationFunction() {
    return 'Drupal.attachBehaviors';
  }

  /**
   * Adds all of the required javascript/css/etc that this model needs to be shown.
   */
  public function addRequiredResources() {
    $this->getCitation(); // Loads some Javascript...
  }

  /**
   * Gets HTML to be rendered into the overview Panel.
   * 
   * @return string
   */
  public function render() {
    return theme('scholar_overview_panel_citation', $this->pid);
  }

  /**
   * Gets the HTML required for the Citation.
   * 
   * @return string
   */
  public function getCitation() {
    $module_path = drupal_get_path('module', 'scholar');
    $citation_file = $module_path . '/citations/apa.csl';
    $csl = new DOMDocument();
    $csl->load($citation_file);
    $citation_api = new IslandoraCitationAPI();
    $html = $citation_api->getCitationHTMLFromPIDAndCSL($csl->saveXML(), array($this->pid));
    $citation_api->addENUS();
    $citation_api->loadCiteprocJavascript();
    return $html;
  }

}

/**
 * Preprocess some junk for the overview.
 * 
 * @param array $variables 
 */
function template_preprocess_scholar_overview_panel_citation(array &$variables) {
  $model = new CitationModel($variables['pid']);
  $variables['citation'] = $model->getCitation();
}