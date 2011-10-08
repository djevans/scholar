dojo.provide("std.language");
doh.register("std.language", [
    function(){
        var test = new StdRhinoTest("language_BaseLocale");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("language_InterCiteJoins");
        doh.assertEqual(test.result, test.run());
    }, 
]);
