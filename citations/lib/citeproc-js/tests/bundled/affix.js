dojo.provide("std.affix");
doh.register("std.affix", [
    function(){
        var test = new StdRhinoTest("affix_PrefixWithDecorations");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("affix_PrefixFullCitationTextOnly");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("affix_TextNodeWithMacro");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("affix_WordProcessorAffixNoSpace");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("affix_SuppressDelimiterCharsWhenFullStopInSuffix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("affix_InterveningEmpty");
        doh.assertEqual(test.result, test.run());
    }, 
]);
