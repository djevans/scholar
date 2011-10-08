dojo.provide("std.discretionary");
doh.register("std.discretionary", [
    function(){
        var test = new StdRhinoTest("discretionary_SuppressEditorSoloFail");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("discretionary_AuthorOnly");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("discretionary_AuthorDateAuthorOnlyThenSuppressAuthor");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("discretionary_SuppressAuthorSolo");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("discretionary_SuppressMultipleAuthors");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("discretionary_CitationNumberSuppressAuthor");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("discretionary_CitationNumberAuthorOnlyThenSuppressAuthor");
        doh.assertEqual(test.result, test.run());
    }, 
]);
