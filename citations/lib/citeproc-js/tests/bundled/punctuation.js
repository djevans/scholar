dojo.provide("std.punctuation");
doh.register("std.punctuation", [
    function(){
        var test = new StdRhinoTest("punctuation_SemicolonDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("punctuation_DelimiterWithStripPeriodsAndSubstitute3");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("punctuation_NoSuppressOfPeriodBeforeSemicolon");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("punctuation_FrenchOrthography");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("punctuation_SuppressPrefixPeriodForDelimiterSemicolon");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("punctuation_DoNotSuppressColonAfterPeriod");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("punctuation_DateStripPeriods");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("punctuation_DelimiterWithStripPeriodsAndSubstitute1");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("punctuation_DefaultYearSuffixDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("punctuation_DelimiterWithStripPeriodsAndSubstitute2");
        doh.assertEqual(test.result, test.run());
    }, 
]);
