dojo.provide("std.integration");
doh.register("std.integration", [
    function(){
        var test = new StdRhinoTest("integration_CitationSortTwice");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_DuplicateItem2");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_DisambiguateAddGivenname2");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_IbidWithDifferentLocators");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_FirstReferenceNoteNumberPositionChange");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_DeleteName");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_YearSuffixOnOffOn");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_SimpleIbid");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_CrossCitationIbidOnInsert");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_DisambiguateAddGivenname1");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_DuplicateItem");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_IbidOnInsert");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_SimpleFirstReferenceNoteNumber");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_SubsequentWhenInterveningFootnote");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("integration_CitationSort");
        doh.assertEqual(test.result, test.run());
    }, 
]);
