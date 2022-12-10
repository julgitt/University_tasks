function sum(...args) {
    var s = 0;
    for(var i = 0; i < args.length; i++){
        s += args[i];
    }
    return s;
}

console.log(sum(1,2,3));
// 6
console.log(sum(1,2,3,4,5));
// 15

    