dojo.provide("std.namespaces");
doh.register("std.namespaces", [
    function(){
        var test = new StdRhinoTest("namespaces_NonNada3");
        doh.assertEqual(test.result, test.run());
    }, 
]);
