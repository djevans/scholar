dojo.provide("std.magic");
doh.register("std.magic", [
    function(){
        var test = new StdRhinoTest("magic_SuppressDuplicateVariableRendering");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_SubsequentAuthorSubstituteNotFooled");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_PunctuationInQuoteDefaultEnglishDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_NameSuffixNoComma");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_PunctuationInQuoteDefaultEnglishSuffix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_SubsequentAuthorSubstitute");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_QuotesAndBraces1");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_MagicCapitalization");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_PunctuationInQuoteFalseSuppressExtra");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_StripPeriodsTrueShortForm");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_HangingIndent");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_SubsequentAuthorSubstituteOfTitleField");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_CitationLabelInBibliography");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_LineSpacingTripleStretch");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_ImplicitYearSuffixExplicitDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_PunctuationInQuoteFalse");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_CitationLabelInCitation");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_StripPeriodsExcludeAffixes");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_SecondFieldAlign");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_SuppressLayoutDelimiterIfPrefixComma");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_PunctuationInQuoteDelimiterTrue");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_LineSpacingDouble");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_PunctuationInQuoteNested");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_NameParticle");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_SuppressExtraTerminalPunctuationAfterTerm");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_StripPeriodsTrue");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_SuperscriptChars");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_ImplicitYearSuffixDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_NameSuffixWithComma");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_PunctuationInQuoteSuffixTrue");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_QuotesAndBraces2");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_SameAuthorNoCollapseNoImplicitComma");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_AllowRepeatDateRenderings");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_PunctuationInQuoteTrueSuppressExtra");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_EntrySpacingDouble");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_SuppressYearIfMatchesVolume");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("magic_StripPeriodsFalse");
        doh.assertEqual(test.result, test.run());
    }, 
]);
