dojo.provide("std.citeprocjs");
doh.register("std.citeprocjs", [
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseSuffixAllCapsSimpleNormalOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseDroppingParticleSortOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseSuffixMixedCaseSimpleNormalOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseNonDroppingParticleSortOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseSuffixAllCapsSimpleSortOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_AuthorListing");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseSuffixMixedCaseForceCommaSortOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseParticleAsName");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseSuffixMixedCaseForceCommaNormalOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ExtraFieldRecognition");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseSuffixAllCapsForceCommaNormalOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseSuffixAllCapsForceCommaSortOrder");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_SubsequentSliceTwoNamesInstitution");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("citeprocjs_ParseSuffixMixedCaseSimpleSortOrder");
        doh.assertEqual(test.result, test.run());
    }, 
]);
