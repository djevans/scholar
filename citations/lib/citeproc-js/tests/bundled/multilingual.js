dojo.provide("std.multilingual");
doh.register("std.multilingual", [
    function(){
        var test = new StdRhinoTest("multilingual_NameSort");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("multilingual_TextPrimaryNonexistent");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("multilingual_TextSortVariableExists");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("multilingual_NameTransliteration");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("multilingual_TextPrimaryExists");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("multilingual_TextSecondaryExists");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("multilingual_TextSortMacroExists");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("multilingual_TextSecondaryNonexistent");
        doh.assertEqual(test.result, test.run());
    }, 
]);
