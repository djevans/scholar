<?php

/**
 * @file
 *
 * Functions for generating a batch export of citations to a single RTF file.
 */

/**
 * Get the batch operations required to generate an RTF file.
 * 
 * @param array $pids
 *   The citation to export to the RTF file.
 * @param sting $style 
 *   The style to apply to the citation before exporting to the RTF.
 * 
 * @return array
 *   The batch operations to create the RTF file.
 */
function citation_exporter_batch_get_rtf_operations(array $pids, $style) {
  $operations = array();
  foreach ($pids as $pid) {
    $operations[] = array('citation_exporter_batch_convert_mods_to_json', array($pid));
  }
  $operations[] = array('citation_exporter_batch_convert_json_to_rtf', array($style));
  $operations[] = array('citation_exporter_batch_redirect', array($_GET['q']));
  return $operations;
}

/**
 * Converts a Fedora Objects MODS to a JSON object that can be used with CiteProc.s
 * 
 * @param string $pid
 *   The citation whose MODS will be converted.
 * @param array $context
 *   The batch context.
 */
function citation_exporter_batch_convert_mods_to_json($pid, array &$context) {
  module_load_include('inc', 'fedora_repository', 'api/fedora_item');
  module_load_include('php', 'citeproc', 'generators/converter');
  $item = new Fedora_Item($pid);
  if ($item->exists() && isset($item->datastreams['MODS'])) {
    $mods = $item->get_datastream_dissemination('MODS');
    $mods = trim($mods);
    if (!empty($mods)) {
      $context['results']['data'][] = convert_mods_to_citeproc_jsons($mods);
    }
  }
}

/**
 * Converts JSON CiteProc objects to an RTF File.
 * 
 * @param string $style
 *   The CSL style to format the JSON citations with.
 * @param array $context 
 *   The batch context.
 */
function citation_exporter_batch_convert_json_to_rtf($style, array &$context) {
  module_load_include('inc', 'csl', 'CSL');
  module_load_include('php', 'citation_exporter', 'class_rtf');
  module_load_include('php', 'CiteProc', 'lib/citeproc-php/CiteProc');
  /* Style */
  $style = CSL::Get($style);
  /* Citations */
  $citeproc = new citeproc($style->saveXML());
  $rtf = new rtf();
  foreach ($context['results']['data'] as $citation) {
    $citation = (object) $citation;
    $citation = json_decode(json_encode($citation)); // HACKKKKK!
    $text = $citeproc->render($citation, 'bibliography');
    $rtf->addText($text . '<br/>');
  }
  /* File */
  $temp_file_dir = file_directory_temp();
  $temp_file_name = file_create_filename("export.rtf", $temp_file_dir);
  $file = fopen($temp_file_name, 'w');
  if ($file !== FALSE) {
    $document = $rtf->getDocument();
    fwrite($file, $document);
    fclose($file);
  }
  /* Batch Values */
  $context['results']['filename'] = $temp_file_name;
  $context['results']['download_filename'] = 'export.rtf';
  $context['results']['mime_type'] = 'application/rtf';
}
