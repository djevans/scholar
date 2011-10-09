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
      /* if (!empty($mods)) {
        $doc = new DOMDocument();
        $doc->loadXML($mods);

        $bibliography = citeproc_bibliography_from_mods($doc);
        return $bibliography->render($style);
        } */
      // HACK!!!!
      module_load_include('inc', 'citeproc', 'CiteProcItem');
      module_load_include('inc', 'citeproc', 'CiteProcCitation');
      module_load_include('inc', 'citeproc', 'CiteProcBibliography');
      
      $style = citeproc_style($style_filename);
      $item = new CiteProcItem();
      $item->setVariable('title', 'Boundaries of Dissent: Protest and State Power in the Media Age');
      $item->addName('author', array(
        'family' => 'D\'Arcus',
        'given' => 'Bruce',
        'static-ordering' => false
      ));
      $item->setVariable('note', 'The apostrophe in Bruce\'s name appears in proper typeset form.');
      $item->setVariable('publisher', 'Routledge');
      $item->setVariable('publisher-place', 'New York');
      $item->setDate('issued', array(
        'date-parts' => array(2006)
      ));
      $item->setVariable('type', 'book');
      $citation = new CiteProcCitation();
      $citation->addItem($item);
      $bibliography = new CiteProcBibliography();
      $bibliography->addCitation($citation);
      return $bibliography->render($style);
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
  $model = new CitationModel($variables['pid']);
  $style = drupal_get_path('module', 'citeproc') . '/data/apa.csl';
  $variables['citation'] = $model->getCitation($style);
}