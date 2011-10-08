dojo.provide("std.locator");
doh.register("std.locator", [
    function(){
        var test = new StdRhinoTest("locator_SimpleLocators");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("locator_WorkaroundTestForSubVerbo");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("locator_TermSelection");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("locator_ParseDate");
        doh.assertEqual(test.result, test.run());
    }, 
]);
