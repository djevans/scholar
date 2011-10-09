// Renders each citation.
Drupal.behaviors.citeproc = function (context){
  var appendCitations = function (citeproc, items) {
    for(id in items) {
      var citation = items[id];
      var output = citeproc.appendCitationCluster(citation);
      jQuery('#' + id + '.citeproc-in-text').html(output);
    }
  }
  var sys = new citeproc_sys();
  var bibliography = sys.retrieveBibliography();
  var style = sys.retrieveStyle(bibliography.style);
  var citeproc = new CSL.Engine(sys, style);
  var abbreviations = bibliography.abbreviation;
  if(abbreviations !== null) {
    citeproc.setAbbreviations(abbreviations);
  }
  appendCitations(citeproc, bibliography.items);
  var output = citeproc.makeBibliography();
  if (output && output.length && output[1].length){
    output = output[0].bibstart + output[1].join("") + output[0].bibend;
    jQuery('#' + bibliography.id + '.citeproc-bibliography').html(output);
  }
}
	