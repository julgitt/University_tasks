//========================================================
// Jakie są różnice między tymi dwoma sposobami? (. [])
//===========================================================

// Różnią się ewaluacją wyrażeń, wyrażenie w [] jest ewaluowane pierwsze,
// a po . jest traktowane dosłownie (bez ewaluacji)

// dzieki temu w [] mozemy iterowac w forze


let tab = [1, 2, 3]

const example = {
    x: 1,
    y: 1000
}

let property = 'x';
console.log('example.property: ' + example.property) // undefinded
console.log('example[property]: ' + example[property]) // dziala

//iteracja
console.log('iteracja:')
for (let key in example) {
    console.log(example[key])
    console.log(example.key)
}

//=========================================================
// Użycie argumentów innego typu niż string dla operatora [] dostępu do składowej
// obiektu.
//==========================================================

console.log('\nUzycie arg. innych niz string:')
console.log('example[0]: ' + example[0]) // co, jeśli liczba?
console.log('example["0"]: ' + example['0'])
console.log('example["x"]: ' + example['x']) // dziala
console.log('example.x: ' + example.x) // dziala



// Co się dzieje jeśli argumentem operatora jest inny obiekt?
console.log('\nJeśli argumentem operatora [] jest inny obiekt:')
console.log('example[tab]: ' + example[tab]) // undefined
console.log('example[tab[0]]: ' + example[tab[0]]) 
tab[3] = 'x'
console.log('example[tab[3]], tab[3] = "x": ' + example[tab[3]]) 

// Jaki wpływ na klucz pod jakim zapisana zostanie wartość ma programista w obu
// przypadkach?
// w tablicy zapisujemy pod indeksem,
// a w obiekcie możemy dać klucz o pewnej nazwie

example[2] = 'y'
example[tab] = 'z'
console.log('\nJaki wpływ na klucz ma programista: \nexample[2]: '+ example[2]) // undefined
console.log('example[tab]: '+ example[tab]) 
//===================================================================================
//Użycie argumentów innego typu niż number dla operatora [] dostępu do tablicy.
//======================================================================================

// Co się dzieje jeśli argumentem operatora jest napis?
console.log('\nJeśli argumentem operatora [] jest napis: ')
console.log('tab["0"]: '+ tab['0']) //dziala
console.log('tab["example"]: ' +tab['example']) //undefinded


// Co się dzieje jeśli argumentem operatora jest inny obiekt?
console.log('\nJeśli argumentem operatora [] jest inny obiekt: ')
console.log('tab[example]: ' + tab[example])
console.log('tab[example.x]: ' + tab[example.x])

// Czy i jak zmienia się zawartość tablicy jeśli zostanie do niej dopisana właściwość
// pod kluczem, który nie jest liczbą?
console.log('\nCo jesli dopiszemy wlasnosc ktora nie jest liczba: ')
tab['example'] = 4
console.log("tab['example']: " + tab['example'])
tab['5'] = 5
console.log("tab['5']: " + tab['5'])
console.log("tab[5]: " + tab[5])


// Czy można ustawiać wartość atrybutu length tablicy na inną wartość niż liczba
// elementów w tej tablicy? Co się dzieje jeśli ustawia się wartość mniejszą niż liczba
// elementów, a co jeśli ustawia się wartość większą niż liczba elementów?


// Zmiana wartości length powoduje:
// - ograniczanie liczby elementów, w przypadku zmniejszania wartości (tracimy info o nich)
// - dodaje puste miejsca w tablicy w przypadku zwiekszania
// Elementy o kluczach typu innego niz number nie wliczaja sie do
// tego ograniczenia i sa wyswietlane zawsze.
console.log('\nZmiana wartosci length: ')
tab.length = 20
console.log(tab)
tab.length = 1
console.log(tab)
tab.length = 20
console.log(tab)


