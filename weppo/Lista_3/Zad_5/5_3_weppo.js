
function createGenerator_with_args(n){
    return function createGenerator() {
        var _state = 0;
        return {
            next : function() {
                return {
                    value : _state,
                    done : _state++ >= n
                };
            }
        };
    };
}

var foo = {
    [Symbol.iterator] : createGenerator_with_args(5)
};
var foo1 = {
    [Symbol.iterator] : createGenerator_with_args('3')
};
var foo2 = {
    [Symbol.iterator] : createGenerator_with_args(50)
};

for ( var f of foo )
    console.log(f);

console.log("\n");

for ( var f of foo1 )
    console.log(f);

console.log("\n");

for ( var f of foo2 )
    console.log(f);
    