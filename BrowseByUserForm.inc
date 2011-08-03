<?php

// $Id$

/**
 * @file
 *
 * Contains the hooks for rendering and processing the Browse By User form.
 */

/**
 * Builds a drupal form for launching a browse by user search.
 * 
 * @param array $form_state 
 * 
 * @return array
 */
function scholar_browse_by_user_form(array &$form_state) {
  $users = array();
  $result = db_query("SELECT uid, name FROM {users} WHERE uid > 1");
  while ($user = db_fetch_object($result)) {
    $users[$user->uid] = $user->name;
  }
  return array(
    'user' => array(
      '#type' => 'select',
      '#options' => $users
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => 'Browse'
    )
  );
}

/**
 * Submit hook for the browse by user form.
 * 
 * @param array $form
 * @param array $form_state 
 */
function scholar_browse_by_user_form_submit(array $form, array &$form_state) {
  
}