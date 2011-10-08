dojo.provide("std.sortseparator");
doh.register("std.sortseparator", [
    function(){
        var test = new StdRhinoTest("sortseparator_SortSeparatorEmpty");
        doh.assertEqual(test.result, test.run());
    }, 
]);
