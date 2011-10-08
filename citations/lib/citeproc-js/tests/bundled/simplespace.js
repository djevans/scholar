dojo.provide("std.simplespace");
doh.register("std.simplespace", [
    function(){
        var test = new StdRhinoTest("simplespace_case1");
        doh.assertEqual(test.result, test.run());
    }, 
]);
