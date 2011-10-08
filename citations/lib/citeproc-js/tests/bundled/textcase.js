dojo.provide("std.textcase");
doh.register("std.textcase", [
    function(){
        var test = new StdRhinoTest("textcase_CapitalsUntouched");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_SentenceCapitalization");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_TitleCaseNonEnglish");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_CapitalizeAll");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_CapitalizeFirstWithDecor");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_TitleCaseNonEnglish2");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_TitleCaseWithInitials");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_Lowercase");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_UppercaseNumber");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_Uppercase");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_TitleCapitalization");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("textcase_CapitalizeFirst");
        doh.assertEqual(test.result, test.run());
    }, 
]);
