/**
 * @file
 *   This javascript creates a sys object for the citeproc-js engine.  This object is meant to allow 
 *   access to abreviations, citation data and localization information that has been made available
 *   through the module's API.
 * @author 
 *   William Panting
 */

/**
 * Constructor
 */
var citeproc_sys = function(){
  return;
};

/**
 * This function will let the citeproc-js engine access to citation data set by the Drupal module
 * @param string id
 *   Identifier for the citaiton data
 */
citeproc_sys.prototype.retrieveItem = function(id){
  return jQuery.parseJSON(Drupal.settings.citeproc.item[id]);
};

/**
 * This function will let the citeproc-js engine access to localization data set by the Drupal module
 * @param string lang
 *   Identifier for the localization data
 */
citeproc_sys.prototype.retrieveLocale = function(lang){
  /*drupal made me do it, Drupal makes sure to preserve a string sent to settings as 
	 * it exists in PHP so we have to re-eval to get the intended value much like jQuery.parseJSON()
	 * is doing in the other sys functions*/
  var locale = eval("'"+Drupal.settings.citeproc.locale[lang]+"'");
  return locale;
};

/**
 * This function will let the citeproc-js engine access to abbreviation data set by the Drupal module
 * @param string name
 *   Identifier for the abbreviation data
 * @param string vartype
 *   Indicates which sub-section of abbreviation data to retrieve
 */
citeproc_sys.prototype.getAbbreviations = function(name, vartype){
  return jQuery.parseJSON(Drupal.settings.citeproc.abbreviation[name][vartype]);
};
