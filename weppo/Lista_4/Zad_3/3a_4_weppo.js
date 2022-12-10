module.exports = { foo };
let b = require('./3b_4_weppo.js');

function foo(n) {
    if ( n > 0 ) {
        console.log( `a: ${n}`);
        b.bar(n-1);
    }
}