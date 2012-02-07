<?php

/**
 * @file
 *
 * Functions for generating a batch export of citations to a single EndNote file.
 */

/**
 * Gets the operations required to batch export a collection of citations to an EndNote file.
 * 
 * @param array $pids 
 *   The citation objects to convert into an EndNote file.
 * 
 * @return array 
 *   The operations required to generate a EndNote file from the given citations.
 */
function citation_exporter_batch_get_endnote_operations(array $pids) {
  $temp_file_dir = file_directory_temp();
  $temp_mods_file = file_create_filename("mods.xml", $temp_file_dir);
  $temp_pids_file = file_create_filename("pids.txt", $temp_file_dir);
  citation_exporter_batch_store_pids_in_file($temp_pids_file, $pids);
  $total = count($pids);
  $mods = new DOMDocument();
  $mods->loadXML('<modsCollection xmlns="http://www.loc.gov/mods/v3" />');
  $mods->save($temp_mods_file);
  $operations = array();
  $operations[] = array('citation_exporter_batch_combine_mods', array($temp_pids_file, $total, $temp_mods_file));
  $operations[] = array('citation_exporter_batch_convert_mods_to_endnote', array($temp_mods_file));
  $operations[] = array('citation_exporter_batch_redirect', array($_GET['q']));
  return $operations;
}

/**
 * Converts the given MODS file to EndNote using bibutils
 * 
 * @param string $filename
 *   The name of the MODS file to convert to EndNote.
 * @param array $context
 *   The batch processes context.
 */
function citation_exporter_batch_convert_mods_to_endnote($mods_filename, array &$context) {
  module_load_include('inc', 'bibutils', 'Bibutils');
  $temp_file_dir = file_directory_temp();
  $endnote_filename = file_create_filename("EndNote_export.xml", $temp_file_dir);
  if (Bibutils::Convert($mods_filename, 'MODS', $endnote_filename, 'Tagged')) {
    $context['results']['filename'] = $endnote_filename;
    $context['results']['mime_type'] = 'application/x-endnote-refer';
    $context['results']['download_filename'] = 'export.enw';
  }
}