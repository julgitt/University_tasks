"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.bar = exports.baz = void 0;
function bar(b) {
    console.log(b);
}
exports.bar = bar;
function baz(c) {
    return c * 10;
}
exports.baz = baz;
function qux(d) {
    return d;
}
exports.default = qux;
