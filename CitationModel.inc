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
    module_load_include('inc', 'citeproc', 'CiteProcJS');
    drupal_add_css(drupal_get_path('module', 'scholar') . '/css/Record.css');
    CiteProcJS::addResources(); // Includes javascript and other fun things.
  }

  /**
   * Gets HTML to be rendered into the overview Panel.
   * 
   * @return string
   */
  public function render() {
    return theme(THEME_SCHOLAR_OVERVIEW_PANEL_CITATION, $this->pid);
  }

  /**
   * Gets the HTML required for the Citation.
   * 
   * @return string
   */
  public function getCitation($style_name) {
    if (isset($this->item->datastreams['MODS'])) {
      $style = citeproc_style($style_name);
      
      $cache_id = "citation_{$this->pid}";
      $cached_raw = cache_get($cache_id);
      
      $bibliography = NULL;
      if (!empty($cached_raw)) {
        $bibliography = citeproc_bibliography_from_raw_array($style, $cached_raw->data);
      }
      else {
        $mods = $this->item->get_datastream_dissemination('MODS');
        $mods = trim($mods);
        if (!empty($mods)) {
          //$doc = new DOMDocument(); //DOM parsing is expensive, and the resultant object is not used (it's passed into citeproc, which eventually does a $doc->saveXML() and then parses with and uses SimpleXML) in this piece of code, so why bother?
          //$doc->loadXML($mods);
          
          $bibliography = citeproc_bibliography_from_mods($style, $mods, $cache_id);
        }
      }
      return array($bibliography->getID(), $bibliography->render());
    }
    return array(NULL, '');
  }

}

/**
 * Preprocess some junk for the overview.
 * 
 * @param array $variables 
 */
function template_preprocess_scholar_overview_panel_citation(array &$variables) {
  module_load_include('inc', 'csl', 'CSL');
  module_load_include('inc', 'islandora_bibliography', 'CitationForm');
  $pid = $variables['pid'];
  //$item = new Fedora_Item($pid);
  $model = new CitationModel($pid);
  $item =& $model->item;
  // Citations
  $styles = CSL::GetNames();
  foreach ($styles as $name) {
    list($id, $html) = $model->getCitation($name);
    $variables['citation'][] = $html;
    $variables['styles'][$id] = $name;
  }
  // Abstract
  if (isset($item->datastreams['MODS'])) {
    $mods = $item->get_datastream_dissemination('MODS');
    $mods = trim($mods);
    if (!empty($mods)) {
      $mods = new SimpleXMLElement($mods);
      $mods->registerXPathNamespace('mods', 'http://www.loc.gov/mods/v3');
      $parts = array(
        'abstract' => '/mods:mods/mods:abstract',
        'subject' => '/mods:mods/mods:subject/mods:topic',
        'grant_number' => '/mods:mods/mods:name[@type="corporate"]/mods:role[mods:roleTerm[@type="text"]="funding agency"]/../mods:description[@type="grant number"]',
        'funding_agency' => '/mods:mods/mods:name[@type="corporate"]/mods:role[mods:roleTerm[@type="text"]="funding agency"]/../mods:namePart',
         'core_facility' => '/mods:mods/mods:note[@type="core facilities"]',
         'source_system' => '/mods:mods/mods:recordInfo/mods:recordOrigin',
         'ccsg_program' => 'string()', // @todo
         'peer_reviewed' => '/mods:mods/mods:note[@type="peer reviewed"]'
      );
      
      foreach ($parts as $key => $xpath) {
        $variables[$key] = implode('<br/>', $mods->xpath($xpath));
      }
    }
  }
}