dojo.provide("std.abbrevs");
doh.register("std.abbrevs", [
    function(){
        var test = new StdRhinoTest("abbrevs_JournalExistsInList");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("abbrevs_JournalMissingFromListAndJournalAbbreviationFieldAlsoMissing");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("abbrevs_SeriesExistsInList");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("abbrevs_Classic");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("abbrevs_JournalMissingFromListButHasJournalAbbreviationField");
        doh.assertEqual(test.result, test.run());
    }, 
]);
