<?php

/**
 * @file
 *
 * Functions for generating a batch export of citations to a single MARCXML file.
 */

/**
 * Gets the operations required to batch export a collection of citations to a MARCXML file.
 * 
 * @param array $pids 
 *   The citation objects to convert into an MARCXML file.
 * 
 * @return array 
 *   The operations required to generate a MARCXML file from the given citations.
 */
function citation_exporter_batch_get_marcxml_operations(array $pids) {
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
  $operations[] = array('citation_exporter_batch_convert_mods_to_marcxml', array($temp_mods_file));
  $operations[] = array('citation_exporter_batch_redirect', array($_GET['q']));
  return $operations;
}

/**
 * Converts the given MODS file to MARCXML using bibutils
 * 
 * @param string $filename
 *   The name of the MODS file to convert to MARCXML.
 * @param array $context
 *   The batch processes context.
 */
function citation_exporter_batch_convert_mods_to_marcxml($mods_filename, array &$context) {
  module_load_include('inc', 'bibutils', 'Bibutils');
  $temp_file_dir = file_directory_temp();
  $marcxml_filename = file_create_filename("marcxml_export.xml", $temp_file_dir);
  
  // convert $mods_filename to $marcxml_filename
  $input = new DOMDocument();
  $input->load($mods_filename);
  
  $path = drupal_get_path('module','scholar');
  $xsl = new DOMDocument();
  $xsl->load($path .'/xsl/MODS2MARC21slim.xsl');
  
  $xsltproc = new XSLTProcessor();
  $xsltproc->importStylesheet($xsl);
  $output = $xsltproc->transformToXML($input);
  file_save_data($output,$marcxml_filename);
  
  $context['results']['filename'] = $marcxml_filename;
  $context['results']['mime_type'] = 'text/xml';
  $context['results']['download_filename'] = 'export.marc.xml';
  
}