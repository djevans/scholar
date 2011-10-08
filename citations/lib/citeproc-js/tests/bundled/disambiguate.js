dojo.provide("std.disambiguate");
doh.register("std.disambiguate", [
    function(){
        var test = new StdRhinoTest("disambiguate_ByCiteGivennameShortFormNoInitializeWith");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixWithEtAlSubequent");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ByCiteRetainNamesOnFailureIfYearSuffixNotAvailable");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AllNamesGenerally");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AddNamesFailureWithAddGivenname");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AndreaEg4");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ByCiteGivennameNoShortFormInitializeWith");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixAtTwoLevels");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ByCiteTwoAuthorsSameFamilyName");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixMidInsert");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_BasedOnSubsequentFormWithBackref");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_CitationLabelInData");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixMixedDates");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearCollapseWithInstitution");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_DifferentSpacingInInitials");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ByCiteGivennameExpandCrossNestedNames");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixFiftyTwoEntries");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_BasedOnEtAlSubsequent");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_HonorFullnameInBibliography");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ToInitialOnly");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AndreaEg2");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_PrimaryNameGenerally");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixTwoPairsFirstNameBibliography");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AllNamesWithInitialsGenerally");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_InitializeWithButNoDisambiguation");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AndreaEg3");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AndreaEg5");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ImplicitYearSuffixOnceOnly");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixAndSort");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_BasedOnSubsequentFormWithLocator");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ByCiteBaseNameCountOnFailureIfYearSuffixAvailable");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AndreaEg1");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixTwoPairsBibliography");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AllNamesSimpleSequence");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixTwoPairsFullNamesBibliography");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ByCiteDisambiguateCondition");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AddNamesFailure");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AddNamesSuccess");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_PrimaryNameWithInitialsLimitedToPrimary");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_DisambiguateWithThree2");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_YearSuffixWithMixedCreatorTypes");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_CitationLabelDefault");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_NoTextElementUsesYearSuffixVariable");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_DisambiguateWithThree");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ByCiteGivennameShortFormInitializeWith");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_ByCiteMinimalGivennameExpandMinimalNames");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("disambiguate_AllNamesBaseNameCountOnFailureIfYearSuffixAvailable");
        doh.assertEqual(test.result, test.run());
    }, 
]);
