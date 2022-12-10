module.exports = { bar };
let a = require('./3a_4_weppo.js');

function bar(n) {
    if ( n > 0 ) {
        console.log( `b: ${n}`);
        a.foo(n-1);
    }
}