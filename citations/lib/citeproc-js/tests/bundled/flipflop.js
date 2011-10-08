dojo.provide("std.flipflop");
doh.register("std.flipflop", [
    function(){
        var test = new StdRhinoTest("flipflop_BoldfaceNodeLevelMarkup");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("flipflop_ItalicsSimple");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("flipflop_QuotesInFieldNotOnNode");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("flipflop_QuotesNodeLevelMarkup");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("flipflop_ItalicsWithOkAndTextcase");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("flipflop_ItalicsFlipped");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("flipflop_ItalicsWithOk");
        doh.assertEqual(test.result, test.run());
    }, 
]);
