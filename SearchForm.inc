<?php

// $Id$

/**
 * @file
 *
 * Contains the hooks for rendering and processing the Quick Search form.
 */

/**
 * Builds a drupal form for launching a quick search.
 * 
 * @param array $form_state 
 * 
 * @return array
 */
function scholar_search_form(array &$form_state) {
    $title = variable_get(VAR_SCHOLAR_SEARCH_FIELD_TITLE, 'title');
    $author = variable_get(VAR_SCHOLAR_SEARCH_FIELD_TITLE, 'author');
    $text = variable_get(VAR_SCHOLAR_SEARCH_FIELD_TITLE, 'text');
    return array(
        'field' => array(
            '#type' => 'select',
            '#options' => array(
                $title => t('Title'),
                $author => t('Author'),
                $text => t('Text'),
            ),
        ),
        'sort' => array(
            '#type' => 'select',
            '#options' => array(
                NULL => 'Order By...',
                'relevance' => t('Relevance'),
                'date' => t('Date'),
            ),
        ),
        'search' => array(
            '#type' => 'textfield',
        ),
        'submit' => array(
            '#type' => 'submit',
            '#value' => 'Search'
        )
    );
}

/**
 * Submit hook for the quick search form.
 * 
 * @param array $form
 * @param array $form_state 
 */
function scholar_search_form_submit(array $form, array &$form_state) {
    $field = $form_state['values']['field'];
    $sort = ($form_state['values']['sort'] != '') ? $form_state['values']['sort'] : 'relevance';
    $search = $form_state['values']['search'];
    $url = preg_replace('/%/', $field, MENU_SCHOLAR_SEARCH, 1);
    $url = preg_replace('/%/', $sort, $url, 1);
    $url = preg_replace('/%/', $search, $url, 1);
    $form_state['redirect'] = $url;
}