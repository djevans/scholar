dojo.provide("std.decorations");
doh.register("std.decorations", [
    function(){
        var test = new StdRhinoTest("decorations_Baseline");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("decorations_NoNormalWithoutDecoration");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("decorations_SimpleFlipFlop");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("decorations_AndTermUnaffectedByNameDecorations");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("decorations_SimpleQuotes");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("decorations_NestedQuotesInnerReverse");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("decorations_NestedQuotes");
        doh.assertEqual(test.result, test.run());
    }, 
]);
