dojo.provide("std.group");
doh.register("std.group", [
    function(){
        var test = new StdRhinoTest("group_SuppressTermWhenNoOutputFromPartialDate");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("group_ComplexNesting");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("group_ShortOutputOnly");
        doh.assertEqual(test.result, test.run());
    }, 
    function(){
        var test = new StdRhinoTest("group_SuppressWithEmptyNestedDateNode");
        doh.assertEqual(test.result, test.run());
    }, 
]);
