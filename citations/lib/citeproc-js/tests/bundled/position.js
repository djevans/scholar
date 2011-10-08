dojo.provide("std.position");
doh.register("std.position", [
    function(){
        var test = new StdRhinoTest("position_TrueInCitation");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("position_IfIbidIsTrueThenSubsequentIsTrue");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("position_FalseInBibliography");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("position_IbidWithLocator");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("position_NearNoteTrue");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("position_NearNoteWithPlugin");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("position_NearNoteFalse");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("position_NearNoteUnsupported");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("position_IfIbidWithLocatorIsTrueThenIbidIsTrue");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("position_FirstTrueOnlyOnce");
        doh.assertEqual(test.result, test.run());
    }, 
]);
