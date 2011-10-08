dojo.provide("std.collapse");
doh.register("std.collapse", [
    function(){
        var test = new StdRhinoTest("collapse_AuthorCollapse");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_TrailingDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_YearSuffixCollapseNoRange");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_CitationNumberRangesMixed");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_CitationNumberRangesMixed3");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_CitationNumberRangesWithAffixesNoCollapse");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_CitationNumberRangesInsert");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_AuthorCollapseDifferentAuthorsOneWithEtAl");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_AuthorCollapseNoDate");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_YearSuffixCollapseNoYearSuffixDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_CitationNumberRangesMixed2");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_YearSuffixImplicitCollapseNoYearSuffixDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_YearSuffixCollapse");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_CitationNumberRangesWithAffixes");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("collapse_AuthorCollapseNoDateSorted");
        doh.assertEqual(test.result, test.run());
    }, 
]);
