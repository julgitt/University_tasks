//Poniżej pokazano przykład funkcji, która w swoim dokmnięciu ”łapie” zmienną lokalną w sposób niekoniecznie zgodny z oczekiwaniami.

function createFs(n) { // tworzy tablicę n funkcji
    var fs = []; // i-ta funkcja z tablicy ma zwrócić i
    for ( var i = 0; i<n; i++ ) {
        fs[i] = function() { //to wykonuje sie z 'opoznieniem', jak jest var to na koniec i = 10 i kazdemu tak ustawi, a przy let wartosci kolejnych i beda zapisane
            return i;
        };
    };
    return fs;
}


var myfs = createFs(10);

console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );
// 10 10 10 // ale wszystkie zwracają 10!?

//==========================================================================================================

//Jednym ze sposobów skorygowania tego nieoczekiwanego zachowania jest zastąpienie var przez let.

function createFs2(n) { // tworzy tablicę n funkcji
    var fs = []; // i-ta funkcja z tablicy ma zwrócić i
    for ( let i = 0; i<n; i++ ) {
        fs[i] = function() {
            return i;
        };
    };
    return fs;
}

var myfs2 = createFs2(10);

console.log( myfs2[0]() );
console.log( myfs2[2]() );
console.log( myfs2[7]() );

//===========================================================================================================

//Istnieje inny sposób, polegający na dodaniu dodatkowego zagnieżdżenia funkcji w funkcji,
//który dla każdej iteracji pętli for utworzy nowy kontekst wiązania domknięcia. 

//Metoda IIFE
function createFs3(n) { // tworzy tablicę n funkcji
    var fs = []; // i-ta funkcja z tablicy ma zwrócić i
    for ( var i = 0; i<n; i++ ) {
        fs[i] = (function(x) {
            return function(){
                return x;
            };
        })(i);
    };
    return fs;
}

var myfs3 = createFs3(10);

console.log( myfs3[0]() );
console.log( myfs3[2]() );
console.log( myfs3[7]() );