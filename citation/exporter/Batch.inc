<?php

/**
 * @file
 *
 * A collection of functions for batch processing files to generate the appropriate file for exporting.
 */
module_load_include('inc', 'citation_exporter', 'BatchExportRIS');
module_load_include('inc', 'citation_exporter', 'BatchExportRTF');
module_load_include('inc', 'citation_exporter', 'BatchExportPDF');

/**
 * Exports a collection of citations to a file.
 * 
 * Launches a Batch process from a submit callback. Otherwise the callee must also call batch_process().
 * 
 * @param array $pids
 *   The collection of citations to export to file.
 * @param string $style
 *   The style to apply to the citation for exporting to a file.
 * @param string $file_format 
 *   The format of the exported file.
 */
function citation_exporter_batch_export(array $pids, $style, $file_format) {
  $operations = array();
  switch ($file_format) {
    case 'RIS':
      $operations = citation_exporter_batch_get_ris_operations($pids);
      break;
    case 'RTF':
      $operations = citation_exporter_batch_get_rtf_operations($pids, $style);
      break;
    case 'PDF':
      $operations = citation_exporter_batch_get_pdf_operations($pids, $style);
      break;
  }
  if (count($operations) > 0) {
    $batch = array(
      'title' => t('Exporting Citations to File'),
      'operations' => $operations,
      'finished' => 'citation_exporter_batch_finished',
    );
    batch_set($batch);
  }
}

/**
 *
 * @param string $filename
 * @param array $pids 
 */
function citation_exporter_batch_store_pids_in_file($filename, array $pids) {
  $file = fopen($filename, 'w');
  foreach ($pids as $pid) {
    fwrite($file, trim($pid) . "\n");
  }
  fclose($file);
}

/**
 *
 * @param type $filename
 * @return type 
 */
function citation_exporter_batch_get_pids_from_file($filename) {
  $file = fopen($filename, 'r');
  $pids = array();
  while (($pid = fgets($file)) !== false) {
    $pids[] = trim($pid);
  }
  fclose($file);
  return $pids;
}

/**
 * Get some pids
 */
function citation_exporter_batch_get_num_pids_from_file($filename, $num = 1) {
  $remaining = 0;
  $ret = array();
  $pids = file($filename);
  if ($pids) {
    for ($i = 0; $i < $num; $i++) {
      $ret[] = trim(array_shift($pids));
    }
    citation_exporter_batch_store_pids_in_file($filename, $pids);
    $remaining = count($pids);
  }
  return array($ret, $remaining);
}

/**
 *
 * @param type $redirect
 * @param array $context 
 */
function citation_exporter_batch_redirect($redirect, array &$context) {
  $context['results']['redirect'] = $redirect;
}

/**
 * Prepare the file generated by the batch process to be downloaded.
 * 
 * @param boolean $successful
 *   Was the batch process succesful?
 * @param array $results
 *   The results returned from the batch process.
 * @param array $operations
 *   The operations that were part of the batch process.
 */
function citation_exporter_batch_finished($successful, array $results, array $operations) {
  module_load_include('inc', 'citation_exporter', 'CitationExporter');
  if ($successful) {
    CitationExporter::PrepareToExport($results['filename'], $results['mime_type'], $results['download_filename'], $results['redirect']);
  }
}