dojo.provide("std.nameorder");
doh.register("std.nameorder", [
    function(){
        var test = new StdRhinoTest("nameorder_Long");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("nameorder_LongNameAsSortDemoteNever");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("nameorder_ShortNameAsSortDemoteNever");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("nameorder_LongNameAsSortDemoteDisplayAndSort");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("nameorder_Short");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("nameorder_ShortDemoteDisplayAndSort");
        doh.assertEqual(test.result, test.run());
    }, 
]);
