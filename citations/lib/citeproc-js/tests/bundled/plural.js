dojo.provide("std.plural");
doh.register("std.plural", [
    function(){
        var test = new StdRhinoTest("plural_NameLabelContextualPlural");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("plural_NameLabelDefaultPlural");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("plural_NameLabelDefaultSingular");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("plural_NameLabelContextualSingular");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("plural_NameLabelAlways");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("plural_NameLabelNever");
        doh.assertEqual(test.result, test.run());
    }, 
]);
