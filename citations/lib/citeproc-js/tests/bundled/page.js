dojo.provide("std.page");
doh.register("std.page", [
    function(){
        var test = new StdRhinoTest("page_Minimal");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("page_Expand");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("page_NoOption");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("page_Chicago");
        doh.assertEqual(test.result, test.run());
    }, 
]);
