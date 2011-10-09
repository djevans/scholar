<?php

/**
 * @file
 *
 * Defines a class that models citeproc-js Citation.
 * 
 * http://gsl-nagoya-u.net/http/pub/citeproc-doc.html#data-input
 */
module_load_include('module', 'citations', 'CiteProcItem');
module_load_include('module', 'citations', 'CiteProcStyle');
module_load_include('module', 'citations', 'CiteProcAbbreviation');

class CiteProcCitation {

  /**
   * 
   * 
   * @var array
   */
  private $items;

  /**
   * Create a CiteProcCitation instance.
   */
  public function __construct() {
    $this->items = array();
  }

  /**
   * Adds a CiteProcItem to this citation, citations can have multiple items.
   * 
   * @param CiteProcItem $item
   *   The item to add to this citation.
   * @param array $config
   *   An array that conforms to the following layout.
   *      locator: a string identifying a page number or other pinpoint location or range within the resource;
   *      label: a label type, indicating whether the locator is to a page, a chapter, or other subdivision of 
   *             the target resource. Valid labels are defined in the  CSL specification.
   *      suppress-author: if true, author names will not be included in the citation output for this cite;
   *      author-only: if true, only the author name will be included in the citation output for this cite -- this 
   *                   optional parameter provides a means for certain demanding styles that require the processor
   *                   output to be divided between the main text and a footnote.
   *      prefix: a string to print before this cite item;
   *      suffix: a string to print after this cite item.
   */
  public function addItem(CiteProcItem $item, array $config = array()) {
    $data = array('id' => $item->getID());
    $this->items[] = array_merge($data, $config);
  }

  /**
   * Renders an in-text citation.
   * 
   * @param CiteProcStyle $style
   * @param CiteProcAbbreviation $abbreviation
   * @param int $note_index 
   *   Indicates the footnote number in which the citation is located within the document. 
   *   Citations within the main text of the document have a noteIndex of zero.
   * 
   * @return string
   *   An html string where the citation will be rendered into.
   */
  public function renderInText(CiteProcStyle $style, CiteProcAbbreviation $abbreviation = NULL, $note_index = 0) {
    /**
     *  @todo Implement
     */
  }

  /**
   * Renders an bibliography entry citation.
   * 
   * @return string
   *   An html string where the citation will be rendered into.
   */
  public function renderBibliographyEntry(CiteProcStyle $style, CiteProcAbbreviation $abbreviation = NULL) {
    
  }

}