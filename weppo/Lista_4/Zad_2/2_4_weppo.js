// @ts-check

/*
Formalnie: zdefiniować funkcję konstruktorową Foo, 
do jej prototypu dodać metodę publiczną Bar,
którą można zawołać na nowo tworzonych instancjach obiektów,
ale w ciele funkcji Bar zawołać funkcję Qux,
która jest funkcją prywatną dla instancji tworzonych przez
Foo (czyli że funkcji Qux nie da się zawołać 
ani wprost na instancjach Foo ani w żaden inny sposób 
niż tylko z wewnątrz metody publicznej Bar).
*/

var Foo = (function() {
    function Qux(){
        console.log("Qux called")
    }
    function Foo(){
        console.log("Foo called")
    }
    Foo.prototype.Bar = function(){
        console.log("Bar called")
        Qux();
        console.log("Qux called from Bar")
    }
    return Foo;
}())

//console.log(Object.getPrototypeOf(Foo));
var foo = new Foo();
console.log(Object.getPrototypeOf(foo))
console.log(Object.getPrototypeOf(foo.Bar))
//console.log(Object.getPrototypeOf(foo.Qux))
foo.Bar();
//foo.Qux();

