dojo.provide("std.initials");
doh.register("std.initials", [
    function(){
        var test = new StdRhinoTest("initials_InitializeFalseToSpace");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("initials_CorrectSpacingWithNameAsSortOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("initials_InitializeFalseToPeriodSpace");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("initials_NonByzantineDisambiguated");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("initials_NonByzantineSimple");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("initials_InitializeFalseToPeriod");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("initials_InitializeFalseToEmptyString");
        doh.assertEqual(test.result, test.run());
    }, 
]);
