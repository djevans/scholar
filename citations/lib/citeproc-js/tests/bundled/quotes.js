dojo.provide("std.quotes");
doh.register("std.quotes", [
    function(){
        var test = new StdRhinoTest("quotes_Punctuation");
        doh.assertEqual(test.result, test.run());
    }, 
]);
