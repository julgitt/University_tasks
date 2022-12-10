function fib_iter(n){
    var a = 1,
        b = 0,
        temp;
    while( n >= 0){
        temp = a;
        a = a + b;
        b = temp;
        n--;
    }
    return b;
}

function fib(n){
    if(n <= 1){
        return 1;
    }    
    return fib(n - 1) + fib(n - 2);
}


function memoize(fn) {
    var cache = {};
    return function(n) {
        if ( n in cache ) {
            return cache[n];
        } 
        else {
            var result = fn(n);
            cache[n] = result;
            return result;
        }
    }
}

var memofib = memoize(fib);


console.time("f(" + 40 + ") rekurencyjnie");
fib(40);
console.timeEnd("f(" + 40 + ") rekurencyjnie");
console.time("f(" + 40 + ") iteracyjnie");
fib_iter(40);
console.timeEnd("f(" + 40 + ") iteracyjnie");

console.time("f(" + 40 + ") z napelnieniem cashe'a");
console.log( memofib(40) );
console.timeEnd("f(" + 40 + ") z napelnieniem cashe'a");

console.time("memoize(f(" + 40 + ")) drugie wyliczenie- z casha");
console.log( memofib(40) );
console.timeEnd("memoize(f(" + 40 + ")) drugie wyliczenie- z casha");
