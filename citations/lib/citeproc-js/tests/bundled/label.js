dojo.provide("std.label");
doh.register("std.label", [
    function(){
        var test = new StdRhinoTest("label_ImplicitForm");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("label_NonexistentNameVariableLabel");
        doh.assertEqual(test.result, test.run());
    }, 
]);
