function rec(n){
    if(n <= 1){
        return 1;
    }    
    return rec(n - 1) + rec(n - 2);
}

function iter(n){
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

for (var i = 10; i <= 40; i++){ 
    console.time("f(" + i + ") rekurencyjnie");
    rec(i);
    console.timeEnd("f(" + i + ") rekurencyjnie");
    console.time("f(" + i + ") iteracyjnie");
    iter(i);
    console.timeEnd("f(" + i + ") iteracyjnie");
}