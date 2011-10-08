dojo.provide("std.dateparser");
doh.register("std.dateparser", [
    function(){
        var test = new StdRhinoTest("dateparser_CheaterSyntax");
        doh.assertEqual(test.result, test.run());
    }, 
]);
