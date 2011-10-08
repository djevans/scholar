dojo.provide("std.spaces");
doh.register("std.spaces", [
    function(){
        var test = new StdRhinoTest("spaces_ParentalSuffixPrefixOverTheHill");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ParentalSuffixDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_SiblingDelimiterPrefix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ExplicitDoubleSpaceSuffix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_SiblingSuffixDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ParentalSuffixPrefixDownhill");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ParentalSuffixPrefixUphill");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ExplicitDoubleSpaceDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ParentalPrefixPrefix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_Prefix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ParentalSuffixSuffixDelimiter");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ExplicitDoubleSpacePrefix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ParentalDelimiterPrefix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ParentalSuffixSuffix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_Doubles");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_ParentalDelimiterPrefixPrefix");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("spaces_SiblingSuffixPrefix");
        doh.assertEqual(test.result, test.run());
    }, 
]);
