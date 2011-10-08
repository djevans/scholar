dojo.provide("std.eclac");
doh.register("std.eclac", [
    function(){
        var test = new StdRhinoTest("eclac_BookWithUnSalesNumber");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("eclac_BookWithUnSalesNumberSpanishStyle");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("eclac_BookFromImf");
        doh.assertEqual(test.result, test.run());
    }, 
]);
