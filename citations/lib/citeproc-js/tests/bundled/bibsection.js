dojo.provide("std.bibsection");
doh.register("std.bibsection", [
    function(){
        var test = new StdRhinoTest("bibsection_Select");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("bibsection_Exclude");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("bibsection_Include");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("bibsection_Quash");
        doh.assertEqual(test.result, test.run());
    }, 
]);
