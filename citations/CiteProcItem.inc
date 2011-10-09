<?php

/**
 * @file
 *
 * Defines a class that models citeproc-js Items.
 */

/**
 * Models a citeproc-js item data structure. This must be registered with the CiteProc singleton to be included
 * on the rendered page.
 */

/**
 * Models CiteProc Items.
 */
class CiteProcItem {

  /**
   * A unique identifier for this object.
   * 
   * @var hash
   */
  private $id;

  /**
   * Create a CiteProcItem.
   */
  public function __construct() {
    $this->id = spl_object_hash($this);
  }

  /**
   * Clone this CiteProcItem.
   */
  public function __clone() {
    $this->id = spl_object_hash($this); // Preserve uniqueness.
  }

  /**
   * Gets the JSON repersentation of this object.
   * 
   * @return string
   *   The JSON repersentation of this object.
   */
  public function toJSON() {
    
  }

}
