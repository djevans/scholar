dojo.provide("std.substitute");
doh.register("std.substitute", [
    function(){
        var test = new StdRhinoTest("substitute_RepeatedNamesOk");
        doh.assertEqual(test.result, test.run());
    }, 
]);
