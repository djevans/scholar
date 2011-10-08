dojo.provide("std.display");
doh.register("std.display", [
    function(){
        var test = new StdRhinoTest("display_SecondFieldAlignClone");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("display_SecondFieldAlignMigratePunctuation");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("display_AuthorAsHeading");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("display_DisplayBlock");
        doh.assertEqual(test.result, test.run());
    }, 
]);
