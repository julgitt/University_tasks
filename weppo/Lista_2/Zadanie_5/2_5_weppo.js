var example = {
    property:  'x',
    foo: function() {
        return `${this.property}`
    },
    get bar() {
        return example.property;
        },
    set bar(i) {
        example.property = i;
    }
}
example.age = 10
example.fun = function() {
    return 5
}

Object.defineProperty( example, 'getter', {
    get : function() {
    return 17;
    }
   });
   Object.defineProperty( example, 'setter', {
    set : function(i) {
        example.property = i;
    }
   });

console.log(example.property);
console.log(example.foo());
console.log(example.bar);
example.bar = 3
console.log(example.bar);
console.log(example.foo());
console.log(example.getter );
example.setter = 4
console.log(example.bar);