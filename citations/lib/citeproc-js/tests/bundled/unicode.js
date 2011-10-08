dojo.provide("std.unicode");
doh.register("std.unicode", [
    function(){
        var test = new StdRhinoTest("unicode_NonBreakingSpace");
        doh.assertEqual(test.result, test.run());
    }, 
]);
