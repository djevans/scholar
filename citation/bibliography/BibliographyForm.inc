<?php

/**
 * @file
 *
 * Functions for including the Manage Bibliography form.
 */

/**
 * This form is called from the menu callback for the 'My Bibliography' page.
 *
 * From here the user can add/remove and export citations.
 *
 * @global string $base_path
 *   The base path of the site.
 *
 * @param array $form_state
 *   The drupal form state.
 *
 * @return array
 *   The drupal form.
 */
function islandora_bibliography_form(array &$form_state) {
  global $base_path;
  drupal_add_css(drupal_get_path('module', 'islandora_bibliography') . '/css/bibliography.css');
  if (isset($_SESSION['bibliography']['export'])) {
    $path = MENU_BIBLIOGRAPHY_EXPORT;
    drupal_set_html_head("<meta http-equiv='refresh' content='0;url=/$path'/>");
  }
  module_load_include('inc', 'islandora_bibliography', 'Bibliography');
  $pids = Bibliography::GetCitations();
  if (empty($pids)) {
    drupal_set_message(t('You have no citations in your bibliography.'));
    return array(
      'redirect' => array(
        '#prefix' => '<p>',
        '#value' => l(t('Return to the Home Page.'), ''),
        '#suffix' => '</p>'
      )
    );
  }
  else {
    module_load_include('inc', 'fedora_repository', 'api/fedora_item');
    $checkboxes = array_fill_keys($pids, '');
    $table = array(
      '#header' => array(theme('table_select_header_cell'), t('Title'), t('Author(s)'), ''),
      '#theme' => THEME_BIBLIOGRAPHY_FORM_TABLE,
      '#tree' => TRUE,
      'selections' => array(
        '#type' => 'checkboxes',
        '#options' => $checkboxes,
      ),
    );
    foreach ($pids as $pid) {
      $title = $authors = 'Missing';
      $item = new Fedora_Item($pid);
      if (isset($item->datastreams['MODS'])) {
        $mods = $item->get_datastream_dissemination('MODS');
        $mods = trim($mods);
        if (!empty($mods)) {
          $mods = new SimpleXMLElement($mods);
          $mods->registerXPathNamespace('mods', 'http://www.loc.gov/mods/v3');
          $title = implode(' ', $mods->xpath('/mods:mods/mods:titleInfo/mods:title'));
          $authors = implode(' ', $mods->xpath('/mods:mods/mods:name/mods:role[mods:roleTerm = "author"]/../mods:namePart[@type="family"]'));
        }
      }
      $table['rows'][] = array(
        '#pid' => $pid,
        'title' => array('#value' => check_plain($pid)),
        'author' => array('#value' => check_plain($authors)),
        'remove' => array(
          '#type' => 'submit',
          '#value' => t('Remove'),
          '#pid' => $pid,
          '#submit' => array('islandora_bibliography_form_remove_citation_submit')
        )
      );
    }
    module_load_include('inc', 'csl', 'CSL');
    $styles = CSL::GetNames();
    return array(
      'fieldset' => array(
        '#type' => 'fieldset',
        '#title' => t('My Citations'),
        '#description' => t('<p>Here you can remove or export citations from your bibliography.</p>'),
        'table' => $table,
        'preview_title' => array(
          '#value' => t('Preview Citations'),
          '#prefix' => '<h4>',
          '#suffix' => '</h4>'
        ),
        'preview_style' => array(
          '#title' => t('Style'),
          '#type' => 'select',
          '#options' => $styles
        ),
        'preview' => array(
          '#type' => 'submit',
          '#value' => t('Preview Selected'),
          '#submit' => array('islandora_bibliography_form_preview')
        ),
        'remove' => array(
          '#type' => 'submit',
          '#value' => t('Remove Selected'),
          '#submit' => array('islandora_bibliography_form_remove')
        ),
        'export_title' => array(
          '#value' => t('Export To File'),
          '#prefix' => '<h4>',
          '#suffix' => '</h4>'
        ),
        'format' => array(
          '#title' => t('Format'),
          '#type' => 'select',
          '#length' => 50,
          '#options' => array(
            'RIS' => 'RIS',
            'RTF' => 'RTF',
            'PDF' => 'PDF',
          )
        ),
        'style' => array(
          '#title' => t('Style'),
          '#type' => 'select',
          '#options' => $styles
        ),
        'export' => array(
          '#type' => 'submit',
          '#action' => 'export',
          '#export' => 'selected',
          '#value' => t('Export Selected'),
          '#submit' => array('islandora_bibliography_form_export')
        )
      )
    );
  }
}

/**
 * Removes one citation from the bibliography.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 */
function islandora_bibliography_form_remove_citation_submit(array $form, array &$form_state) {
  module_load_include('inc', 'islandora_bibliography', 'Bibliography');
  $pid = $form_state['clicked_button']['#pid'];
  Bibliography::RemoveCitation($pid);
  drupal_set_message(t('Removed Citation'));
}

/**
 * Previews the selected citations from the bibliography.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 */
function islandora_bibliography_form_preview(array $form, array &$form_state) {
  $selections = $form_state['values']['table']['selections'];
  _islandora_bibliography_form_preview_selections($selections, $form_state['values']['preview_style']);
}

/**
 * Removes the selected citations from the bibliography.
 *
 * @param array $form
 * @param array $form_state
 */
function islandora_bibliography_form_remove(array $form, array &$form_state) {
  module_load_include('inc', 'islandora_bibliography', 'Bibliography');
  $selections = array_filter($form_state['values']['table']['selections']);
  $pids = array_keys($selections);
  Bibliography::RemoveCitations($pids);
  drupal_set_message(t('Removed %num Citation(s)', array('%num' => count($pids))));
}

/**
 * Exports the selected pids to file.
 *
 * @param array $form
 * @param array $form_state
 */
function islandora_bibliography_form_export(array $form, array &$form_state) {
  $selections = array_filter($form_state['values']['table']['selections']);
  $pids = array_keys($selections);
  islandora_bibliography_export_citations($pids, $form_state['values']['style'], $form_state['values']['format']);
}

/**
 * Export the users selections.
 *
 * Helper function for islandora_bibliography_form_submit().
 *
 * @param array $selections
 *   The users selections, the keys are pids and the values indicated if it was selected.
 * @param string $style
 *   The name of the style file to use.
 */
function _islandora_bibliography_form_preview_selections(array $selections, $style) {
  module_load_include('inc', 'fedora_repository', 'api/fedora_item');
  module_load_include('inc', 'citeproc', 'CiteProcJSBibliography');
  drupal_add_css(drupal_get_path('module', 'islandora_bibliography') . '/css/export.css');
  $style = citeproc_style($style);
  $bibliography = new CiteProcJSBibliography($style);
  $selections = array_filter($selections);
  foreach ($selections as $pid => $selected) {
    $item = new Fedora_Item($pid);
    if (isset($item->datastreams['MODS'])) {
      $mods = trim($item->get_datastream_dissemination('MODS'));
      if (!empty($mods)) {
        $doc = new DOMDocument();
        $doc->loadXML($mods);
        $citation = citeproc_citation_from_mods($doc);
        $bibliography->addCitation($citation);
      }
    }
  }
  $output = $bibliography->render();
  $output .= l(t('Return to the Bibliography.'), 'bibliography');
  print theme('page', $output, FALSE);
  exit();
}

/**
 * Theme's a form table for this module.
 *
 * @param array $element
 *   A Drupal Form Element.
 *
 * @return sting
 *   HTML that renders a table of settings for datastreams.
 */
function theme_islandora_bibliography_form_table(array $element) {
  $rows = array();
  foreach (element_children($element['rows']) as $child) {
    $setting = $element['rows'][$child];
    $pid = $setting['#pid'];
    $fields = array(
      drupal_render($element['selections'][$pid]) // First field is a checkbox
    );
    foreach (element_children($setting) as $property) {
      $field = $setting[$property];
      $fields[] = drupal_render($field);
    }
    $rows[] = array(
      'data' => $fields,
      'class' => isset($setting['#attributes']['class']) ? $setting['#attributes']['class'] : NULL
    );
  }
  $attributes = isset($element['#id']) ? array('id' => $element['#id']) : NULL;
  return theme_table($element['#header'], $rows, $attributes);
}