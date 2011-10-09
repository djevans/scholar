<?php

/**
 * @file
 *
 * Defines a class that models citeproc-js Citation.
 * 
 * http://gsl-nagoya-u.net/http/pub/citeproc-doc.html#data-input
 */
module_load_include('module', 'citations', 'CiteProcItem');


class CiteProcCitation {

  // Render struct
  //  Include the style
  //  Any Abbre
  //  extra properties used by citeproc-js
  public function __construct() {
    
  }

  public function addItem(CiteProcItem $item, array $properties) {
    
  }

}