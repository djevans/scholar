dojo.provide("std.bibheader");
doh.register("std.bibheader", [
    function(){
        var test = new StdRhinoTest("bibheader_SecondFieldAlign");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("bibheader_EntryspacingDefaultValueOne");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("bibheader_EntryspacingExplicitValueZero");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("bibheader_SecondFieldAlignWithAuthor");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("bibheader_SecondFieldAlignWithNumber");
        doh.assertEqual(test.result, test.run());
    }, 
]);
