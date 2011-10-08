dojo.provide("std.generate");
doh.register("std.generate", [
    function(){
        var test = new StdRhinoTest("generate_BibTrigger");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("generate_CiteTrigger");
        doh.assertEqual(test.result, test.run());
    }, 
]);
