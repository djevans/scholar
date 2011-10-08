dojo.provide("std.parallel");
doh.register("std.parallel", [
    function(){
        var test = new StdRhinoTest("parallel_HackedChicago");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("parallel_SuppressYearIfSuppressedInFirstCite");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("parallel_Bibliography");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("parallel_FrenchCaseAndComments");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("parallel_JournalArticleSimple");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("parallel_JournalArticleReverse");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("parallel_TrailingIbid");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("parallel_TreatiesMcGill");
        doh.assertEqual(test.result, test.run());
    }, 
]);
