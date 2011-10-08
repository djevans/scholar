dojo.provide("std.layout");
doh.register("std.layout", [
    function(){
        var test = new StdRhinoTest("layout_MultipleWithItemLocator");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("layout_SimpleMultiple");
        doh.assertEqual(test.result, test.run());
    }, 
]);
