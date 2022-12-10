/*
Napisać program, który wypisze na ekranie zapytanie o imię użytkownika, odczyta z
konsoli wprowadzony tekst, a następnie wypisze Witaj {imię}. 
Użyć dowolnej techniki do spełnienia tego wymagania,
 ale nie korzystać z zewnętrznych modułów z npm a wyłącznie 
 z obiektów z biblioteki standardowej (wszystkie te techniki sprowadzają się 
do jakiejś formy dojścia do strumienia process.stdin).
Wskazówka: https://stackoverflow.com/q/8128578/941240
*/
const readline = require('readline');

var cl = readline.createInterface( process.stdin, process.stdout );
var question = function(q) {
    return new Promise( (res, rej) => {
        cl.question( q, answer => {
            res(answer);
        })
    });
};

(async function main() {
    var answer = "";
    while ( answer.length < 1 ) {
        answer = await question('Please enter your name: ');
    }
    cl.close();
    console.log( 'Hello ' + answer + "!");
})();
