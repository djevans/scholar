<?php

/**
 * @file
 *
 * Defines a class that models citeproc-js Bibliography.
 *
 * http://gsl-nagoya-u.net/http/pub/citeproc-doc.html#data-input
 */
module_load_include('inc', 'citeproc', 'CiteProcCitation');
module_load_include('inc', 'citeproc', 'CiteProcStyle');
module_load_include('inc', 'citeproc', 'CiteProcAbbreviation');

/**
 * Models a Citation.
 */
class CiteProcBibliography {

  /**
   * Uniquely identifies this object
   *
   * @var array
   */
  private $id;

  /**
   * A array of CiteProcCitations's to include in this citation.
   *
   * @var array
   */
  private $citations;

  /**
   * Create a CiteProcBibliography instance.
   */
  public function __construct() {
    $this->id = spl_object_hash($this);
    $this->citations = array();
  }

  /**
   * Clone this CiteProcBibliography.
   */
  public function __clone() {
    $this->id = spl_object_hash($this); // Preserve uniqueness.
  }

  /**
   * Gets this objects identifier.
   *
   * @return hash
   *   This objects ID.
   */
  public function getID() {
    return $this->id;
  }

  /**
   * Adds a CiteProcCitation, citations can have multiple items.
   *
   * @param CiteProcCitation $citation
   *   The item to add to this citation.
   */
  public function addCitation(CiteProcCitation $citation) {
    $citation_id = $citation->getID();
    $this->citations[$citation_id] = $citation;
  }

  /**
   * Creates an array of data that will be converted to JSON and used to render the bibliography.
   *
   * @param CiteProcStyle $style
   *   The CSL style to render with. Must be CSL version 1.0.
   * @param CiteProcAbbreviation $abbreviation
   *   Any abbreviations we wan't to apply.
   *
   * @return array
   *   Data that will be converted to JSON and used to render the bibliography.
   */
  private function createRenderData(CiteProcStyle $style, CiteProcAbbreviation $abbreviation = NULL) {
    $data = array(
      'id' => $this->id,
      'style' => $style->getID(),
      'abbreviation' => isset($abbreviation) ? $abbreviation->getID() : NULL,
      'items' => array()
    );
    foreach ($this->citations as $id => $citation) {
      $data['items'][$id] = $citation->toJSON();
    }
    return $data;
  }

  /**
   * Renders an bibliography.
   *
   *
   * @param CiteProcStyle $style
   *   The CSL style to render with. Must be CSL version 1.0.
   * @param CiteProcAbbreviation $abbreviation
   *   Any abbreviations we wan't to apply.
   *
   * @return string
   *   An html string where the in-text citation will be rendered into.
   */
  public function render(CiteProcStyle $style, CiteProcAbbreviation $abbreviation = NULL) {
    module_load_include('inc', 'citeproc', 'CiteProc');
    $data = $this->createRenderData($style, $abbreviation);
    $citeproc = CiteProc::getInstance();
    $citeproc->addBibliography($data);
    return '<div id="' . $this->id . '" class="citeproc-bibliography">[Page generation failure.  The bibliography processor requires a browser with Javascript enabled.]</div>';
  }

}