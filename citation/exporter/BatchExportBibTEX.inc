<?php

/**
 * @file
 *
 * Functions for generating a batch export of citations to a single BibTEX file.
 */

/**
 * Gets the operations required to batch export a collection of citations to a BibTEX file.
 * 
 * @param array $pids 
 *   The citation objects to convert into an BibTEX file.
 * 
 * @return array 
 *   The operations required to generate a BibTEX file from the given citations.
 */
function citation_exporter_batch_get_bibtex_operations(array $pids) {
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
  $operations[] = array('citation_exporter_batch_convert_mods_to_bibtex', array($temp_mods_file));
  $operations[] = array('citation_exporter_batch_redirect', array($_GET['q']));
  return $operations;
}

/**
 * Converts the given MODS file to BibTEX using bibutils
 * 
 * @param string $filename
 *   The name of the MODS file to convert to BibTEX.
 * @param array $context
 *   The batch processes context.
 */
function citation_exporter_batch_convert_mods_to_bibtex($mods_filename, array &$context) {
  module_load_include('inc', 'bibutils', 'Bibutils');
  $temp_file_dir = file_directory_temp();
  $bibtex_filename = file_create_filename("bibtex_export.xml", $temp_file_dir);
  if (Bibutils::Convert($mods_filename, 'MODS', $bibtex_filename, 'BibTEX')) {
    $context['results']['filename'] = $bibtex_filename;
    $context['results']['mime_type'] = 'application/x-bibtex';
    $context['results']['download_filename'] = 'export.bib';
  }
}