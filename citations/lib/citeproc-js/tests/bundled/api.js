dojo.provide("std.api");
doh.register("std.api", [
    function(){
        var test = new StdRhinoTest("api_UpdateItemsReshuffle");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("api_UpdateItemsDeleteDecrementsByCiteDisambiguation");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("api_UpdateItemsDelete");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("api_SuppressAuthor");
        doh.assertEqual(test.result, test.run());
    }, 
]);
