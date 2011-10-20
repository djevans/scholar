<?php

/**
 * @file
 *
 * Functions for generating a batch export of citations to a single PDF file.
 */
module_load_include('inc', 'citation_exporter', 'BatchExportRTF');

/**
 * Get the batch operations required to generate an PDF file.
 * 
 * @param array $pids
 *   The citation to export to the PDF file.
 * @param sting $style 
 *   The style to apply to the citation before exporting to the PDF.
 * 
 * @return array
 *   The batch operations to create the PDF file.
 */
function citation_exporter_batch_get_pdf_operations(array $pids, $style) {
  $operations = array();
  foreach ($pids as $pid) {
    $operations[] = array('citation_exporter_batch_convert_mods_to_json', array($pid));
  }
  $operations[] = array('citation_exporter_batch_convert_json_to_rtf', array($style));
  $operations[] = array('citation_exporter_batch_convert_rtf_to_pdf', array());
  $operations[] = array('citation_exporter_batch_redirect', array($_GET['q']));
  return $operations;
}

/**
 * Converts an RTF document to a PDF.
 * 
 * We can't directly generate the PDF so this is a good work around.
 * 
 * @param array $context
 *   The batch context.
 */
function citation_exporter_batch_convert_rtf_to_pdf(array &$context) {
  $output = array();
  $return_value = FALSE;
  $filename = $context['results']['filename'];
  exec('soffice.bin --headless -convert-to pdf ' . $filename, $output, $return_value);
  if ($return_value === 0) {
    $filename = preg_replace('/\.rtf$/', '.pdf', $context['results']['filename']);
    $context['results']['filename'] = $filename;
    $context['results']['download_filename'] = 'export.pdf';
    $context['results']['mime_type'] = 'application/pdf';
  }
  else {
    $context['success'] = FALSE;
    $context['finished'] = 1;
  }
}
