/*Węzeł drzewa binarnego (Tree) to obiekt który przechowuje referencje do swojego
lewego i prawego syna oraz wartość (np. liczba lub napis). Proszę w notatkach do wykładu
odnaleźć implementację takiego węzła i nauczyć się używać zdefiniowanej tam funkcji
konstruktorowej.*/


/*Na wykładzie pokazano jak do prototypu funkcji konstruktorowej dodać generator, który
powoduje enumerowanie zawartości drzewa ”wgłąb”:*/

/*function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

Tree.prototype[Symbol.iterator] = function*() {
    yield this.val;
    if ( this.left ) yield* this.left;
    if ( this.right ) yield* this.right;
}

var root = new Tree( 1,
    new Tree( 2, new Tree( 3 ) ), new Tree( 4 ));

for ( var e of root ) {
    console.log( e );
}
// 1 2 3 4*/

/*Państwa zadaniem jest zaproponować definicję iteratora (zaimplementowanego wprost jako
funkcja zwracająca obiekt zawierający next... lub jako generator z yield), który enume-
ruje zawartość drzewa ”wszerz”. Dla podanego wyżej przykładowego drzewa wynikiem
enumeracji powinno być 1 4 2 3 i oczywiście w ogólnym przypadku, wyniki enumerowa-
nia ”wgłąb” i ”wszerz” są różne, poza tym że w obu przypadkach pierwszym zwróconym
wynikiem jest wartość z korzenia drzewa.
Wskazówka: iterator nie będzie rekursywny, tak jak ten ”wgłąb”. Zamiast tego, iterator
wykorzystuje pomocniczą strukturę danych - kolejkę (jak za pomocą tablicy i funkcji
splice w Javascript uzyskać efekt kolejki, czyli dodawanie elementów na koniec kolejki,
ściąganie elementów z początku kolejki?) - oraz następujący algorytm
(a) do kolejki włoż korzeń drzewa
1
(b) powtarzaj dopóki kolejka jest niepusta
i. wyjmij węzeł z kolejki
ii. do kolejki włóż lewy i prawy podwęzeł (jeśli istnieją)
iii. zwróć (value lub yield) wartość węzła
Pytanie dodatkowe, niepunktowane: co by się stało, gdyby zamiast kolejki użyć stosu
(dodawanie elementów na koniec stosu, ściągane elementów z końca stosu)?
*/


function Tree2(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

Tree2.prototype[Symbol.iterator] = function*() {
    var queue = [this];
    while (queue.length > 0) {
        let node = queue.splice(0,1);
        if (node[0].left) 
            queue.push(node[0].left);
        if (node[0].right) 
            queue.push (node[0].right);
        yield node[0].val;
    }
}


var root2 = new Tree2(1, new Tree2(2, new Tree2(3, new Tree2(6))), new Tree2(4, new Tree2(8)));

//     1
//   2  4
//  3  8
// 6
for ( var e of root2 ) {
    console.log( e );
}