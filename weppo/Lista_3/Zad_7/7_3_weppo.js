// Próba iterowania nieskończonych iteratorów/generatorów takich jak w poprzednim
// zadaniu powoduje problem - taki nieskończony iterator/generator zawsze zwraca kolejną
// wartość i naiwne iterowanie nigdy się nie kończy.
// Pokazać jak rozwiązać ten problem za pomocą dodatkowej funkcji generującej, która jako
// argumenty przyjmuje iterator/generator oraz liczbę elementów które powinna zwrócić i
// zwraca dokładnie taką, skończoną liczbę elementów:

function fib_generator() {
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
                done : false,
            };
        }
    }
}


function *fib(cur = 1, next = 1) {
    yield cur;
    yield* fib(next, cur + next);
}

function* take(it, top) {
    for (var i = 0; i <= top; i++){
        yield it.next().value;
    }
}
// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (let num of take( fib(), 10 ) ) {
    console.log(num);
}
console.log("\n");
for (let num of take( fib_generator(), 10 ) ) {
    console.log(num);
}