dojo.provide("std.form");
doh.register("std.form", [
    function(){
        var test = new StdRhinoTest("form_TitleShortNoLong");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("form_TitleShort");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("form_TitleTestNoLongFalse");
        doh.assertEqual(test.result, test.run());
    }, 
]);
