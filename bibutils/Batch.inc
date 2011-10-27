<?php

/**
 * @file
 *
 * Functions for batch use of Bibutils. While Bibutils doesn't provide any batch operations directly, these
 * functions will be used by other modules for Doing batch ingests/exports and what not.
 */

/**
 * Removes a single record from the EndNote XML file and returns it.
 * 
 * @param string $filename
 *   The filename of a EndNote XML Document.
 * 
 * @return DOMDocument
 *   A single EndNote XML record if found, FALSE otherwise.
 */
function bibutils_batch_get_endnote_record($filename) {
  $endnote = new DOMDocument();
  $endnote->load($filename);
  $xpath = new DOMXPath($endnote);
  $results = $xpath->query('/xml/records/record');
  $documents = array();
  if ($results->length >= 1) {
    $doc = new DOMDocument();
    $child = $results->item(0); // Get Record
    $doc->loadXML('<xml><records>' . $endnote->saveXML($child) . '</records></xml>');
    $child->parentNode->removeChild($child); // Remove Record
    $endnote->save($filename);
    return $doc;
  }
  return FALSE;
}

/**
 * Removes a single record from the RIS file and returns it.
 * 
 * @param string $filename
 *   The filename of the RIS file.
 * 
 * @return string
 *   The RIS record if successful, FALSE otherwise.
 */
function bibutils_batch_get_ris_record($filename) {
  /**
   * Get the first Record from the RIS File.
   */
  $file = fopen($filename, 'r');
  $record = '';
  while (($line = fgets($file)) !== false) {
    $trimed_line = trim($line);
    if (!empty($trimed_line)) { // Ignore blank lines
      $record .= $line; // Store the line in outgoing record
      if ($trimed_line == 'ER  -') {
        break;
      }
    }
  }
  /**
   * Put the remaining text into a temp file.
   */
  $temp_file_dir = file_directory_temp();
  $temp_filename = file_create_filename("ris_temp.ris", $temp_file_dir);
  $temp_file = fopen($temp_filename, 'w');
  while (!feof($file)) {
    fwrite($temp_file, fread($file, 1024));
  }
  fclose($file);
  fclose($temp_file);
  /**
   * Replace the RIS file with the shorter temp file.
   */
  unlink($filename);
  rename($temp_filename, $filename);
  return (trim($record) == '') ? FALSE : $record;
}

/**
 * An internal function that is not meant to be used outside of this file.
 * 
 * Generates a DOMDocument for each <mods> element within the given MODS document.
 * 
 * @param DOMDocument $mods 
 *   A Valid MODS Document.
 * 
 * @return DOMDocument[]
 *   An array of DOMDocuments that repersent each <mods> record within the <modsCollection>
 *
function _split_mods_collection_into_mulitiple_documents(DOMDocument $mods) {
  $xpath = new DOMXPath($mods);
  $xpath->registerNamespace('mods', 'http://www.loc.gov/mods/v3');
  $results = $xpath->query('/mods:modsCollection/mods:mods');
  $documents = array();
  $count = $results->length;
  for ($i = 0; $i < $count; $i++) {
    $doc = new DOMDocument();
    $child = $results->item($i);
    $child->setAttribute('xmlns', 'http://www.loc.gov/mods/v3');
    $doc->loadXML($mods->saveXML($child));
    $documents[] = $doc;
  }
  return $documents;
}*/