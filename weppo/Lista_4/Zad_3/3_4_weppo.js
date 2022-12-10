/*
Zademonstrować w praktyce tworzenie własnych modułów oraz ich włączanie do
kodu za pomocą require. Czy możliwa jest sytuacja w której dwa moduły tworzą cykl
(odwołują się do siebie nawzajem)? Jeśli nie - wytłumaczyć dlaczego, jeśli tak - pokazać
przykład implementacji.
*/

let a = require('./3a_4_weppo.js');
a.foo(5);
