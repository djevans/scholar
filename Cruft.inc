<?php

/**
 * @file
 * 
 * Functions and other cruft not currently in use but may get referenced/reintergrated in the near future.
 */
//define('MENU_SCHOLAR_SEARCH', 'ir/search/%/%/%');
//define('MENU_SCHOLAR_BROWSE_USER', 'ir/user/%');
//define('MENU_SCHOLAR_BROWSE_DEPARTMENT', 'ir/department/%');
//define('MENU_SCHOLAR_ADMIN_SETTINGS', 'admin/settings/institutional_repository');
//define('THEME_SCHOLAR_RECORD', 'ir_record');
//define('THEME_SCHOLAR_BROWSE_USER', 'ir_browse_by_name');
//define('THEME_SCHOLAR_BROWSE_DEPARTMENT', 'ir_browse_by_department');
//define('THEME_SCHOLAR_SEARCH', 'ir_search');
/*
  $items[MENU_SCHOLAR_SEARCH] = array(
  'title' => 'Institutional Repository',
  'page callback' => 'scholar_search',
  'page arguments' => array(2, 3, 4),
  'access callback' => 'user_access',
  'access arguments' => array('access content'),
  'type' => MENU_CALLBACK,
  );
  $items[MENU_SCHOLAR_BROWSE_DEPARTMENT] = array(
  'title' => 'Institutional Repository By Department',
  'page callback' => 'scholar_role',
  'access callback' => 'user_access',
  'type' => MENU_CALLBACK,
  'access arguments' => array(PERM_SCHOLAR_VIEW_RESEARCH),
  );
  $items[MENU_SCHOLAR_BROWSE_USER] = array(
  'title' => 'Institutional Repository By User Name',
  'page callback' => 'scholar_by_name',
  'access callback' => 'user_access',
  'type' => MENU_CALLBACK,
  'access arguments' => array(PERM_SCHOLAR_VIEW_RESEARCH),
  );
  $items[MENU_SCHOLAR_ADMIN_SETTINGS] = array(
  'title' => t('Institutional Repository'),
  'description' => t('Configure Settings'),
  'page callback' => 'drupal_get_form',
  'page arguments' => array('scholar_admin_settings'),
  'access arguments' => array('administer site configuration'),
  'file' => 'scholar.admin.inc',
  'type' => MENU_NORMAL_ITEM,
  ); */

module_load_include('inc', 'scholar', 'IrClass');

/**
 * Menu callback for 'fedorair/ir_edit_refworks' 
 * 
 * @param string $pid
 * 
 * @return string
 *   HTML Rendering of the drupal form.
 */
function scholar_edit_refworks($pid) {
  module_load_include('inc', 'scholar', 'RefworksForm');
  return drupal_get_form('scholar_refworks_form', $pid);
}

/**
 * Builds a drupal form for adding a new datastream.
 * 
 * @todo determine if this is called from anywhere.
 * 
 * @param array $form_state
 * @param string $pid
 * 
 * @return array 
 */
function scholar_add_ir_datastream_form(array $form_state, $pid) {
  $datastream_form = new IrClass();
  return $datastream_form->build_add_datastream_form($pid);
}

/**
 * Submit hook for the add datasteam form.
 * 
 * @param array $form
 * @param array $form_state 
 */
function scholar_add_ir_datastream_form_submit(array $form, array &$form_state) {
  $ir = new IrClass();
  $ir->addStreamFormSubmit($form_state['values']['form_id'], $form_state['values']);
}

/**
 * Menu callbacke for 'fedorair/ir_create_roles_for_users'
 * 
 * @todo determine what this function does.
 * 
 * @return string
 */
function scholar_create_roles_for_users() {
  $irClass = new IrClass();
  $irClass->get_and_create_roles();
  return 'created roles and associated users.';
}

/**
 * Implements a validation hook for the fedora_repository ingest form.
 * 
 * Ensures that a file is uploaded and it is of the correct type.
 * 
 * @param array $form
 * @param array $form_state
 */
function validation_for_refworks(array $form, array &$form_state) {
  if ($form_state['clicked_button']['#id'] == 'edit-submit') {
    switch ($form_state['storage']['step']) {
      case 1:
        $form_state['rebuild'] = TRUE;
        break;
      case 2:
// Get the uploaded file.
        $validators = array();
        if (!empty($_FILES['files']['name']['pdf-file-location'])) {
          $fileObject = file_save_upload('pdf-file-location', $validators);
          file_move($fileObject->filepath, 0, 'FILE_EXISTS_RENAME');
          $form_state['values']['pdf-file-location'] = $fileObject->filepath;
        }
        if (file_exists($form_state['values']['pdf-file-location'])) {
          $file = $form_state['values']['pdf-file-location'];
          $extention = strtolower(pathinfo($file, PATHINFO_EXTENSION));
          if ($extention != 'pdf') {
            form_set_error('pdf-file-location', t("$file does not appear to be a valid PDF."));
            file_delete($file);
            return;
          }
        }
        $form_state['rebuild'] = FALSE;
        break;
    }
  }
}

/**
 * Implements Form Alter Hook.
 * 
 * Alters the fedora_repository ingest form. It modifies the description of the datastream upload field so that it only
 * references 'Ref Works' documents.
 * 
 * @param array $form
 * @param array $form_state 
 */
function scholar_form_fedora_repository_ingest_form_alter(array &$form, array &$form_state) {
  array_unshift($form['#validate'], 'validation_for_refworks');
  $form['indicator']['ingest-file-location']['#title'] = t('Upload Refworks Document');
  $form['indicator']['ingest-file-location']['#description'] = t('Upload refworks xml document containing one or more records.');
}

/**
 * Implements the Theme Hook function for the ir_record theme.
 *
 * @param $variables
 */
function template_preprocess_ir_search(array &$variables) {
  drupal_add_css(drupal_get_path('module', 'scholar') . '/css/Search.css');
  $variables['search_results'] = islandora_solr_search($variables['query'], $variables['fq'], $variables['dismax']);
}

/*
THEME_SCHOLAR_RECORD => array(
      'arguments' => array('pid' => NULL),
      'template' => 'templates/Record',
    ),
    THEME_SCHOLAR_SEARCH => array(
      'template' => 'templates/Search',
      'arguments' => array('query' => NULL, 'fq' => NULL, 'dismax' => NULL)
    ),
    THEME_SCHOLAR_BROWSE_USER => array(
      'template' => 'templates/BrowseName',
    ),
    THEME_SCHOLAR_BROWSE_DEPARTMENT => array(
      'template' => 'templates/BrowseDepartment',
    ),*/

/**
 * Implements the Theme Hook function for the ir_record theme.
 *
 * @param $variables
 */
function template_preprocess_ir_record(array &$variables) {
  module_load_include('inc', 'Fedora_Repository', 'api/fedora_item');
  drupal_add_css(drupal_get_path('module', 'scholar') . '/css/Record.css');
  $pid = $variables['pid'];
  $item = new Fedora_Item($pid);
  foreach ($item->datastreams as $dsid => $attributes) {
    $view = 'fedora/repository/' . $pid . '/' . $dsid;
    $download = 'fedora/repository/object_download/' . $pid . '/' . $dsid;
    $variables['rows'][] = array($attributes['label'], l(t('View'), $view), l(t('Download'), $download), $attributes['MIMEType']);
  }
}


/**
 * Renders the Search page.
 * 
 * @param string $field
 * @param string $order 
 *  
 * @return string
 */
function scholar_search($field, $order, $value) {
  module_load_include('inc', 'scholar', 'SearchForm');
  module_load_include('inc', 'islandora_solr_search', 'IslandoraSolrQueryProcessor');
  $fields = array(
    'title' => 'dc.title',
    'author' => 'dc.contributor',
    'text' => 'Text'
  );
  $field = $fields[$field]; // Remap Field to query friendly one.
  $query = $field . ':' . $value;
  return theme(THEME_SCHOLAR_SEARCH, $query);
}


/**
 * Menu callback for 'fedorair/ir_full_record'
 * 
 * Renders the full record this object.
 * 
 * @param string $pid
 * 
 * @return string
 *   HTML
 */
function scholar_full_record($pid) {
  return theme(THEME_SCHOLAR_RECORD, $pid);
}
