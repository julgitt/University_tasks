"use strict";
function fib(n) {
    if (n <= 1) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}
function memoize(fn) {
    const cache = new Map();
    return function (input) {
        if (cache.has(input)) {
            return cache.get(input);
        }
        else {
            const result = fn(input);
            cache.set(input, result);
            return result;
        }
    };
}
var memofib = memoize(fib);
console.time("f(" + 40 + ") z napelnieniem cashe'a");
console.log(memofib(40));
console.timeEnd("f(" + 40 + ") z napelnieniem cashe'a");
console.time("memoize(f(" + 40 + ")) drugie wyliczenie- z casha");
console.log(memofib(40));
console.timeEnd("memoize(f(" + 40 + ")) drugie wyliczenie- z casha");
