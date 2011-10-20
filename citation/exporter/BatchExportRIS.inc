<?php

/**
 * @file
 *
 * Functions for generating a batch export of citations to a single RIS file.
 */

/**
 * Gets the operations required to batch export a collection of citations to an RIS file.
 * 
 * @param array $pids 
 *   The citation objects to convert into an RIS file.
 * 
 * @return array 
 *   The operations required to generate a RIS file from the given citations.
 */
function citation_exporter_batch_get_ris_operations(array $pids) {
  $temp_file_dir = file_directory_temp();
  $temp_file = file_create_filename("mods.xml", $temp_file_dir);
  $mods = new DOMDocument();
  $mods->loadXML('<modsCollection xmlns="http://www.loc.gov/mods/v3" />');
  $mods->save($temp_file);
  foreach ($pids as $pid) {
    $operations[] = array('citation_exporter_batch_combine_mods', array($temp_file, $pid));
  }
  $operations[] = array('citation_exporter_batch_convert_mods_to_ris', array($temp_file));
  $operations[] = array('citation_exporter_batch_redirect', array($_GET['q']));
}

/**
 * Adds and existing Fedora Objects MODS datastream to the given MODS file.
 * 
 * @param string $filename
 *   The name of the mods file to append this citations mods to.
 * @param string $pid
 *   The citation object's pid.
 * @param array $context 
 *   The batch processes context.
 */
function citation_exporter_batch_combine_mods($filename, $pid, array &$context) {
  module_load_include('inc', 'fedora_repository', 'api/fedora_item');
  $mods = new DOMDocument();
  $mods->load($filename);
  $item = new Fedora_Item($pid);
  if ($item->exists() && isset($item->datastreams['MODS'])) {
    $datastream = $item->get_datastream_dissemination('MODS');
    $datastream = trim($datastream);
    if (!empty($mods)) {
      $doc = new DOMDocument();
      $doc->loadXML($datastream);
      $node = $mods->importNode($doc->documentElement, TRUE);
      $mods->documentElement->appendChild($node);
      $mods->save($filename);
    }
  }
}

/**
 * Converts the given MODS file to RIS using bibutils
 * 
 * @param string $filename
 *   The name of the MODS file to convert to RIS.
 * @param array $context
 *   The batch processes context.
 */
function citation_exporter_batch_convert_mods_to_ris($filename, array &$context) {
  $context['results']['filename'] = bibutils_mods_file_to_ris_document($filename);
  $context['results']['mime_type'] = 'application/x-Research-Info-Systems';
  $context['results']['download_filename'] = 'export.ris';
}