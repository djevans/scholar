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
  $temp_file_dir = file_directory_temp();
  $temp_file = file_create_filename("rtf_export.txt", $temp_file_dir);
  $operations = array();
  foreach ($pids as $pid) {
    $operations[] = array('citation_exporter_batch_append_citation_to_text_file', array($temp_file, $style, $pid));
  }
  $operations[] = array('citation_exporter_batch_convert_txt_to_rtf', array($temp_file));
  $operations[] = array('citation_exporter_batch_redirect', array($_GET['q']));
  return $operations;
}

/**
 * Appends a citation generated from citeproc-php to the provided text file.
 * 
 * @param string $filename
 *   The name of the text file to append the citation to.
 * @param string $style
 *   The name of the style used to render the citation.
 * @param type $pid
 *   The object from whom the metadata for the citation is taken.
 * @param array $context 
 *   The batch context.
 */
function citation_exporter_batch_append_citation_to_text_file($filename, $style, $pid, array &$context) {
  module_load_include('inc', 'fedora_repository', 'api/fedora_item');
  module_load_include('php', 'citeproc', 'generators/converter');
  module_load_include('php', 'CiteProc', 'lib/citeproc-php/CiteProc');
  module_load_include('inc', 'csl', 'CSL');
  $item = new Fedora_Item($pid);
  if ($item->exists() && isset($item->datastreams['MODS'])) {
    $mods = $item->get_datastream_dissemination('MODS');
    $mods = trim($mods);
    if (!empty($mods)) {
      $style = CSL::Get($style);
      $citeproc = new citeproc($style->saveXML());
      $json = (object) convert_mods_to_citeproc_jsons($mods);
      $citation = json_decode(json_encode($json)); // HACKKKKK!
      $text = $citeproc->render($citation, 'bibliography');
      $file = fopen($filename, 'a');
      if ($file) {
          fwrite($file, $text . "<br/><br/>"); // I know the <br/> look out of place but its cause this is an intermediate document and the rtf class will replace them with newlines.
        fclose($file);
      }
    }
  }
  $context['results']['filename'] = $filename;
  $context['results']['download_filename'] = 'export.txt';
  $context['results']['mime_type'] = 'text/txt';
}

/**
 * Converts TXT file to an RTF File.
 * 
 * @param string $style
 *   The CSL style to format the JSON citations with.
 * @param array $context 
 *   The batch context.
 */
function citation_exporter_batch_convert_txt_to_rtf($filename, array &$context) {
  module_load_include('php', 'citation_exporter', 'class_rtf');
  $text = '';
  $file = fopen($filename, 'rw');
  while (!feof($file)) {
    $text .= fread($file, 1024);
  }
  fclose($file);
  $data = json_decode($json);
  $rtf = new rtf();
  $rtf->addText($text);
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
