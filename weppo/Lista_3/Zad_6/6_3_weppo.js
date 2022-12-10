/*Zarówno iteratory jak i generatory mogą być ”nieskończone”, czyli zawsze zwracać
kolejną wartość. Zaimplementować takie nieskończone generatory dla liczb fibonacciego:
zwykły iterator (zwracający obiekt z funkcją next) oraz generator (czyli funkcję wewnętrznie używającą yield do zwracania kolejnych wartości).*/

//iterator
function fib_generator(n){
    return function fib() {
        var a = 0;
        var b = 1;
        var c;
        return {
            next : function() {
                c = b;
                b = a;
                a += c;
                return {
                    value : a,
                    done : a >= n,
                };
            }
        }
    }
}

//generator
function *fib(cur = 1, next = 1) {
    yield cur;
    yield* fib(next, cur + next);
}


//W obu przypadkach możliwe jest iterowanie się po kolejnych wartościach za pomocą pokazanej na wykładzie konstrukcji

var fib_gen = fib_generator(40);
var _it1 = fib_gen();
var _it2 = fib();
for ( var _result; _result = _it1.next(), !_result.done; ) {
    console.log( "iterator: " + _result.value );
    console.log( "generator: " + (_it2.next()).value + "\n");
}

//Czy w którymś z przypadków możliwe jest iterowanie się po kolejnych wartościach za pomocą for-of:
console.log("\nfor-of dla wersji z generatorem:")
for (var i of fib()) {
    if (i <= 40)
        console.log(i);
    else
        return;
}