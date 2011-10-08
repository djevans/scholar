dojo.provide("std.etal");
doh.register("std.etal", [
    function(){
        var test = new StdRhinoTest("etal_ShortFormOfName");
        doh.assertEqual(test.result, test.run());
    }, 
]);
