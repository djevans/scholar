dojo.provide("std.variables");
doh.register("std.variables", [
    function(){
        var test = new StdRhinoTest("variables_ShortForm");
        doh.assertEqual(test.result, test.run());
    }, 
]);
