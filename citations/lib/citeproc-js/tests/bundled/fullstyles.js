dojo.provide("std.fullstyles");
doh.register("std.fullstyles", [
    function(){
        var test = new StdRhinoTest("fullstyles_ChicagoNoteWithBibliographyWithPublisher");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("fullstyles_APA");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("fullstyles_ChicagoArticleTitleQuestion");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("fullstyles_ChicagoAuthorDateSimple");
        doh.assertEqual(test.result, test.run());
    }, 
]);
