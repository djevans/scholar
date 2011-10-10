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
    return NULL; // Nothing at the moment...
  }

  /**
   * Adds all of the required javascript/css/etc that this model needs to be shown.
   */
  public function addRequiredResources() {
    module_load_include('inc', 'citeproc', 'CiteProc');
    drupal_add_css(drupal_get_path('module', 'scholar') . '/css/Record.css');
    CiteProc::addResources(); // Includes javascript and other fun things.
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
  public function getCitation($style_filename) {
    if (isset($this->item->datastreams['MODS'])) {
      $mods = $this->item->get_datastream_dissemination('MODS');
      $mods = trim($mods);
      if (!empty($mods)) {
        $doc = new DOMDocument();
        $doc->loadXML($mods);
        $style = citeproc_style($style_filename);
        $bibliography = citeproc_bibliography_from_mods($style, $doc);
        return $bibliography->render();
      }
    }
    return '';
  }

}

/**
 * Preprocess some junk for the overview.
 * 
 * @param array $variables 
 */
function template_preprocess_scholar_overview_panel_citation(array &$variables) {
  $pid = $variables['pid'];
  $item = new Fedora_Item($pid);
  $model = new CitationModel($pid);
  // Citations
  $styles = array(
    'apa.csl' => 'APA',
    'annotated.csl' => 'Annotated',
    'nih.csl' => 'NIH',
    'nlm.csl' => 'NLM',
  );
  foreach ($styles as $file => $name) {
    $style = drupal_get_path('module', 'citeproc') . '/data/' . $file;
    $variables['citation'][] = $model->getCitation($style);
  }
  // Abstract
  if (isset($item->datastreams['MODS'])) {
    $mods = $item->get_datastream_dissemination('MODS');
    $mods = trim($mods);
    if (!empty($mods)) {
      $mods = new SimpleXMLElement($mods);
      $mods->registerXPathNamespace('mods', 'http://www.loc.gov/mods/v3');
      $variables['abstract'] = implode('<br/>', $mods->xpath('/mods:mods/mods:abstract'));
    }
  }
}