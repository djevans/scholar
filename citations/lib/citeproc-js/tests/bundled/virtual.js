dojo.provide("std.virtual");
doh.register("std.virtual", [
    function(){
        var test = new StdRhinoTest("virtual_PageFirst");
        doh.assertEqual(test.result, test.run());
    }, 
]);
