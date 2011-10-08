dojo.provide("std.institutions");
doh.register("std.institutions", [
    function(){
        var test = new StdRhinoTest("institutions_SimplePersonalInstitution");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_MixedPeopleAndOrganizationsInTextImplicitChop");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_SimpleShortLong");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_ItalicInstitutionHarvard");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_QuotesSuppressCommaSplit");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_MixedPeopleAndOrganizationsMaybeUseFirst");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_FirstOnly");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_SubcommitteeCommittee");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_ItalicInstitutionHarvardBib");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_TwoThreeOrFourInstitutions");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_FirstAndLast");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("institutions_MixedPeopleAndOrganizationsAlwaysUseFirst");
        doh.assertEqual(test.result, test.run());
    }, 
]);
