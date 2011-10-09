<?php

/**
 * @file
 *
 * Citation Class.
 */

/**
 * Singleton, for storing the data and citation items.
 */
class CiteProc {

  /**
   * The default locale. This local is always loaded.
   */
  static $DEFAULT_LOCALE = 'en-US';
  /**
   * The location of the locale files relative to this module.
   */
  const LOCALE_DIRECTORY = '/lib/citeproc-js/locale/';
  /**
   * The locale's avaliable to this module.
   */
  static $LOCALES = array(
    'af-ZA' => 'locales-af-ZA.xml',
    'ar-AR' => 'locales-ar-AR.xml',
    'bg-BG' => 'locales-bg-BG.xml',
    'ca-AD' => 'locales-ca-AD.xml',
    'cs-CZ' => 'locales-cs-CZ.xml',
    'da-DK' => 'locales-da-DK.xml',
    'de-AT' => 'locales-de-AT.xml',
    'de-CH' => 'locales-de-CH.xml',
    'de-DE' => 'locales-de-DE.xml',
    'el-GR' => 'locales-el-GR.xml',
    'en-GB' => 'locales-en-GB.xml',
    'en-US' => 'locales-en-US.xml',
    'es-ES' => 'locales-es-ES.xml',
    'et-EE' => 'locales-et-EE.xml',
    'fa-IR' => 'locales-fa-IR.xml',
    'fr-FR' => 'locales-fr-FR.xml',
    'he-IL' => 'locales-he-IL.xml',
    'hu-HU' => 'locales-hu-HU.xml',
    'is-IS' => 'locales-is-IS.xml',
    'it-IT' => 'locales-it-IT.xml',
    'ja-JP' => 'locales-ja-JP.xml',
    'km-KH' => 'locales-km-KH.xml',
    'ko-KR' => 'locales-ko-KR.xml',
    'mn-MN' => 'locales-mn-MN.xml',
    'nb-NO' => 'locales-nb-NO.xml',
    'nl-NL' => 'locales-nl-NL.xml',
    'nn-NO' => 'locales-nn-NO.xml',
    'pl-PL' => 'locales-pl-PL.xml',
    'pt-BR' => 'locales-pt-BR.xml',
    'pt-PT' => 'locales-pt-PT.xml',
    'ro-RO' => 'locales-ro-RO.xml',
    'ru-RU' => 'locales-ru-RU.xml',
    'sk-SK' => 'locales-sk-SK.xml',
    'sl-SI' => 'locales-sl-SI.xml',
    'sr-RS' => 'locales-sr-RS.xml',
    'sv-SE' => 'locales-sv-SE.xml',
    'th-TH' => 'locales-th-TH.xml',
    'tr-TR' => 'locales-tr-TR.xml',
    'uk-UA' => 'locales-uk-UA.xml',
    'vi-VN' => 'locales-vi-VN.xml',
    'zh-CN' => 'locales-zh-CN.xml',
    'zh-TW' => 'locales-zh-TW.xml'
  );

  /**
   * An array of all the items that have been added.
   * 
   * @var array
   */
  private $items;

  /**
   * Gets the singleton instance of this class.
   * 
   * @staticvar CiteProc $instance
   * @return CiteProc 
   */
  public static function getInstance() {
    static $instance = NULL;
    if ($instance === NULL) {
      $instance = new CiteProc();
    }
    return $instance;
  }

  /**
   * Creates a CiteProc instance. 
   * 
   * Includes the default locale.
   */
  private function __construct() {
    $this->includeLocale(self::$DEFAULT_LOCALE);
    $this->items = array();
  }

  /**
   * Stores data required by citeproc-js in the drupal settings object.
   * 
   * @param array $data 
   *   The data to store in the drupal settings object.
   */
  private function storeInSettings(array $data) {
    drupal_add_js(array('citeproc' => $data), 'setting');
  }

  /**
   * Registers a CiteProcAbbreviation with the citeproc-js api.
   * 
   * Note after adding a CiteProcAbbreviation, subsequent changes to the 
   * CiteProcAbbreviation will have no affect on citeproc-js.
   * 
   * @param CiteProcAbbreviation $abbreviation 
   *   The abbreviation to register.
   */
  public function addAbbreviation(CiteProcAbbreviation $abbreviation) {
    if (array_search($this->abbreviations[$abbreviation->id])) {
      drupal_set_message('CiteProcItem %id, has already been added to the page.', array('%id' => $item->id));
    }
    else {
      $data = array(
        'abbreviations' => array(
          $item->id => $item->toJSON()
        )
      );
      $this->storeInSettings($data);
    }
  }

  /**
   * Registers a CiteProcItem with the citeproc-js api.
   * 
   * Note after adding a CiteProcItem, subsequent changes to the CiteProcItem 
   * will have no on citeproc-js.
   * 
   * @param CiteProcItem $item 
   *   The item to register.
   */
  public function addItem(CiteProcItem $item) {
    if (array_search($this->items[$item->id])) {
      drupal_set_message('CiteProcItem %id, has already been added to the page.', array('%id' => $item->id));
    }
    else {
      $data = array(
        'items' => array(
          $item->id => $item->toJSON()
        )
      );
      $this->storeInSettings($data);
    }
  }

  /**
   * Adds an existing local.
   * 
   * @param string $name
   *   A $key in this objects self::$LOCALES array.
   * @return boolean
   *   TRUE on success, FALSE otherwise.
   */
  public function addLocale($name) {
    if (isset(self::$LOCALES[$name])) {
      $locale = new DOMDocument();
      $filename = drupal_get_path('module', 'citations') . self::LOCALE_DIRECTORY . self::$LOCALES[$name];
      $locale->load($filename);
      $this->addCustomLocale($name, $locale->saveXML());
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Adds a custom locale.
   * 
   * @param string $name
   *   The name of the locale, used to identify it uniquely.
   * @param DOMDocument $locale
   *   The locale definition. Must be CSL version 1.0.
   */
  public function addCustomLocale($name, DOMDocument $locale) {
    $data = array(
      'locales' => array(
        $name => $locale->saveXML()
      )
    );
    $this->storeInSettings($data);
  }

  /**
   * Adds a CSL style, which can be used to format citaions.
   * 
   * @param string $name
   *   The name of the style.
   * @param DOMDocument $style
   *   The CSL style definition. Must be CSL version 1.0.
   */
  public function addStyle($name, DOMDocument $style) {
    $data = array(
      'styles' => array(
        $name => $locale->saveXML()
      )
    );
    $this->storeInSettings($data);
  }

}



class CiteProcCitation {
  // Render struct
  //  Include the style
  //  Any Abbre
  //  extra properties used by citeproc-js
}

class CiteProcBibliography {
  // Collection of CiteProcCitation instuctions
}
