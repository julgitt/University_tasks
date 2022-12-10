let foo = new String('foo');
bar = 'string'
console.log(typeof foo); //object bo stworzylismy instancje obiektu klasy String
console.log(foo instanceof String); // true, mozna sprawdzyc wszystko co zainicjowane operatorem "new"
console.log(typeof bar); //string bo stworzylismy prymitywna wartosc string
console.log(bar instanceof String); // false