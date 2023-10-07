# Programowanie funkcyjne lista 1

## Zadanie 1 (3p)

<br>
Jaki jest typ wyrażenia fun x -> x? 

```ocaml=
'a -> 'a = fun (* 'a - for all types 'a *)
```

<br>
Napisz wyrażenie, którego wartością też jest funkcja identycznościowa, ale które ma typ int -> int. 

```ocaml=
fun x : int = x
```

<br>
Napisz wyrażenia, których typami są:
• (’a -> ’b) -> (’c -> ’a) -> ’c -> ’b

```ocaml=
fun f g x -> f (g x)
```

<br>
• ’a -> ’b -> ’a

```ocaml=
fun x y -> x
```

<br>
• ’a -> ’a -> ’a

```ocaml=
fun (x:'a) (y:'a) -> x;;
```
<br>
Czy potrafisz napisać wyrażenie typu ’a?
<br>

Nie, jest to typ polimorficzny, który może oznaczać każdy tym, ale nie moge go bezpośrednio stworzyć. Wyrażenie musi mieć określone typowanie,
nie może być dowolnego typu.


---

## Zadanie 2 (1p)
<br> 
Napisz funkcję typu ’a -> ’b.

```ocaml=
let rec f x = f x;;
```
<br>
## Zadanie 3 (6p)
<br> 
Strumień (tj. nieskończony ciąg) elementów typu t możemy reprezentować za pomocą funkcji s: int -> t w taki sposób, że wartością wyrażenia s 0 jest pierwszy element strumienia, wyrażenia s 1 — drugi itd.
Używając powyższej reprezentacji zdefiniuj następujące funkcje działające na strumieniach (tam, gdzie to możliwe, funkcje te powinny być polimorficzne, tj. powinny działać na strumieniach o elementach dowolnego typu):

• hd, tl — funkcje zwracające odpowiednio głowę i ogon strumienia;
<br>
```ocaml=
let stream x = x + 1 (* Przykładowy strumień *)

let hd s = s 0

let tl s = fun f x -> s (x + 1)
```

<br>
• add — funkcja, która dla zadanego strumienia tworzy nowy strumień, którego każdy element jest większy o zadaną stałą od odpowiadającego mu elementu oryginalnego strumienia;

```ocaml=
let add stream x = fun y -> stream(y) + x
```

<br>
• map — funkcja, która dla zadanego strumienia tworzy nowy strumień, którego każdy element jest wynikiem obliczenia zadanej funkcji dla argumentu będącego odpowiadającym mu elementem oryginalnego strumienia (tak, jak map dla list skończonych);


```ocaml=
let map stream f = fun x -> f (stream x)
```

<br>
• map2 — jak wyżej, ale dla podanej funkcji dwuargumentowej i dwóch strumieni, np. map2 (+) s1 s2 policzy sumę dwóch strumieni po współrzędnych;


```ocaml=
let map2 stream1 stream2 f = fun x -> f (stream1 x)(stream2 x)
(* jeżeli chcemy mieć różne współrzędne w strumieniach, to do fun x dodajemy jeszcze drugi argument *)
```

```ocaml=
• replace — funkcja, która dla zadanego indeksu n, wartości a i strumienia s tworzy nowy strumień, w którym wszystkie wartości są takie jak w strumieniu s, oprócz n-tego elementu, który ma wartość a;
:::

```ocaml=
let replace n a s = fun x -> if x = n then a else s x;;
```

<br>
• take_every — funkcja, która dla zadanego indeksu n i strumienia s tworzy nowy strumień złożony z co n-tego elementu strumienia s.

```ocaml=
let take_every n s = fun x -> s (n * x)
```
<br>
Zdefiniuj przykładowe strumienie i przetestuj swoją implementację.

*Wskazówka: nie szukaj w internecie o strumieniach, bo strumienie zwykle reprezentuje się w zupełnie inny sposób. W tym zadaniu chcemy przećwiczyć funkcje wyższego rzędu, więc strumienie reprezentujemy tak jak reprezentowaliście ciągi na Analizie Matematycznej: jako funkcje z liczb naturalnych w elementy ciągu (strumienia).*


---
## Zadanie 4 (1p)
<br>
Dla strumieni z poprzedniego zadania zdefiniuj funkcję scan, która dla zadanej funkcji f: ’a -> ’b -> ’a, wartości początkowej a: ’a i strumienia s elementów typu ’b tworzy nowy strumień, którego każdy element jest wynikiem „zwinięcia” początkowego segmentu strumienia s aż do bieżącego elementu włącznie za pomocą funkcji f, tj. w strumieniu wynikowym element o indeksie n ma wartość (f (. . . (f (f a (s 0)) (s 1)) . . .) (s n)),
Wskazówka: liczby naturalne mają strukturę. 
Od czego zaczyna się nowy strumień? 
Jak mając n-ty element nowego strumienia policzyć następny?


```ocaml=
let stream x = x + 1
let f x y = x

let rec scan (f: 'a -> 'b -> 'a) (a : 'a) ) (s : int -> 'b) =
        fun x -> 
            if x = 0 then f a (s 0)
            else f ((scan f a s) (x - 1)) (s x);;
            
(scan f 10 stream) 5
f ((scan f 10 stream) (4) (stream 5))
f ((f ((scan f 10 stream) (3) (stream 4))) 6)
f ((f (( f (( scan f 10 stream (2) (stream 3))) 5))) 6)
...
f ... (f (f 10  1) 2) ... 6 = x
```
---
<br>
## Zadanie 5 (2p)
<br>
Zdefiniuj funkcję tabulate, której wynikiem powinna być lista elementów strumienia leżących w zadanym zakresie indeksów.
Pusta lista to [], natomiast binarny operator (::) dołącza element z przodu listy (tak jak cons w Rackecie).
Wykorzystaj możliwość definiowania parametrów opcjonalnych dla funkcji — niech początek zakresu indeksów będzie opcjonalny i domyślnie równy 0.

*Przykład: pierwszy argument funkcji f w deklaracji 
let f ?(x=0) y = x + y
ma etykietę x i jest opcjonalny, a jego wartość domyślna wynosi 0. 
Wyrażenie (f 3) jest równoważne wyrażeniu (f ~x:0 3) (i ma wartość 3), zaś wartością wyrażenia (f ~x:42 3) jest 45.*
<br>

```ocaml=
let rec tabulate ?(left=0) right stream = 
    if left > right then []
    else stream left :: tabulate ~left:(left + 1) right stream;;  
    
    
tabulate ~left:2 8 stream;;
tabulate 8 stream;;
```
---
## Zadanie 6 (2p)
<br>
Ile różnych wartości mają zamknięte wyrażenia typu ’a -> ’a -> ’a, których obliczenie nie wywołuje żadnych efektów ubocznych (tj. które zawsze kończą działanie, nie wywołują wyjątków, nie używają operacji wejścia/wyjścia itp.)? Okazuje się, że jest ich dokładnie tyle, ile potrzeba, by reprezentować za ich pomocą wartości logiczne prawdy i fałszu! Zdefiniuj odpowiednie wartości ctrue i cfalse typu ’a -> ’a -> ’a.

```ocaml=
let ctrue = 'a -> 'a -> 'a =
  fun x y -> x;;
  
let cfalse = 'a -> 'a -> 'a =
  fun x y -> y;;
```
<br> 
oraz funkcje o podanych niżej sygnaturach implementujące operacje koniunkcji i alternatywy oraz konwersji między naszą reprezentacją a wbudowanym typem wartości logicznych.

• cand, cor: (’a -> ’a -> ’a) -> (’a -> ’a -> ’a) -> ’a -> ’a -> ’a

```ocaml=
let cand p q x y =
  p (q (ctrue x y) (cfalse x y)) (cfalse x y);;
(* ('a -> 'b -> 'c) -> ('b -> 'b -> 'a) -> 'b -> 'b -> 'c *)
let cor p q x y = p (ctrue x y) (q (ctrue x y) (cfalse x y)) 
(* ('a -> 'b -> 'c) -> ('a -> 'a -> 'b) -> 'a -> 'a -> 'c *)

(*let cand p q = if p == ctrue && p == q then p else cfalse;;*)
(* 'a - (ctrue x y) *)
(* 'b - zwracane przez q *)
(* 'c - zwracane przez p *)
(* p i q są typu ctrue / cfalse, ale powyżej nie jest to narzucone, może to być jakiś inny typ, który nie wiadomo jaki typ zwraca )
```

• cbool_of_bool: bool -> ’a -> ’a -> ’a

```ocaml=
let cbool_of_bool p : bool = 
    if p 
    then ctrue 
    else cfalse;;

```
<br>
• bool_of_cbool: (bool -> bool -> bool) -> bool


```ocaml=
let bool_of_cbool p : (bool -> bool -> bool) =
        p true false;;
```

<br>
Zastanów się, czemu typy niektórych z powyższych funkcji znalezione przez algorytm rekonstrukcji typów różnią się od podanych powyżej.

*Wskazówka: o takiej reprezentacji wartości logicznych można myśleć jak o funkcjach, które biorą dwa parametry: reprezentację prawdy i reprezentację fałszu i wybierają jedną z nich. 
Implementując operacje cand i cor weź wszystkie argumenty.*

<br>
---
## Zadanie 7 (2p)
<br>
Wartościami zamkniętych wyrażeń typu (’a -> ’a) -> ’a -> ’a są wszystkie funkcje postaci (f, x) → f^n (x) dla dowolnej liczby naturalnej n, więc można użyć tego typu do reprezentacji liczb naturalnych. 
Zdefiniuj liczbę zero, operację następnika, operacje dodawania i mnożenia, funkcję sprawdzającą, czy dana liczba jest zerem, a także konwersje między naszą reprezentacją a wbudowanym typem liczb całkowitych (nie przejmuj się liczbami ujemnymi):

• zero : (’a -> ’a) -> ’a -> ’a
<br>
```ocaml=
let zero (f : 'a -> 'a) z = z;;
```

<br>
• succ : ((’a -> ’a) -> ’a -> ’a) -> (’a -> ’a) -> ’a -> ’a

```ocaml=
let succ num =
    fun f z -> f (num f z);;
    (*('a -> 'b) -> 'c -> 'a) -> ('a -> 'b) -> 'c -> 'b *)
```
<br>
• add, mul : ((’a -> ’a) -> ’a -> ’a) ->
((’a -> ’a) -> ’a -> ’a) -> (’a -> ’a) -> ’a -> ’a

```ocaml=
let add num1 num2 = 
        fun f z -> (num1 f (num2 f z));;

let mul num1 num2 = 
        fun f z -> (num1 (num2 f)) z;;
        
(*('a -> 'b -> 'c) -> ('d -> 'a) -> 'd -> 'b -> 'c*)

(*num1 = 2, num2 = 2 = succ(succ zero)*)
(* num1 f = succ(succ zero) -> num 1 = f(f zero) = succ(succ (succ (succ zero))) *)
```
<br>
• is_zero : ((’a -> ’a) -> ’a -> ’a) -> ’a -> ’a -> ’a


```ocaml=
let is_zero num  = num (
    fun _ -> cfalse) ctrue;;
```
<br>
• cnum_of_int : int -> (’a -> ’a) -> ’a -> ’a
```ocaml=
let rec cnum_of_int (a : int) = if a = 0 then zero else succ(cnum_of_int (a - 1)) ;; 
```
<br>
• int_of_cnum : ((int -> int) -> int -> int) -> int

```ocaml=
let int_of_cnum (a : ((int -> int) -> int -> int)) 
    = a (fun a -> a + 1) 0;; 
```
<br>
W funkcji is_zero typ wyniku (’a -> ’a -> ’a) to reprezentacja wartości Boole’owskich z poprzedniego zadania.
Zastanów się, czemu typy niektórych z powyższych funkcji znalezione przez algorytm rekonstrukcji typów różnią się od podanych powyżej.
*Wskazówka: podobnie jak w poprzednim zadaniu o takich liczbach można myśleć jak o funkcjach, które biorą jako parametry reprezentację następnika i zera i z nich budują odpowiednią wartość.*

<br>
---
## Zadanie 8 (3p)
<br>
Typy funkcji int_of_cnum oraz bool_of_cbool z poprzednich zadań nie są nie w pełni zadowalające, bo wymuszają by podanie reprezentacje liczb i wartości Boole’owskich operowały odpowiednio na liczbach i wartościach logicznych.
Można by ulec złudzeniu, że oczekiwany typ funkcji bool_of_cbool powinien mieć postać (’a -> ’a -> ’a) -> bool, ale nie jest to prawdą. 
Na przykład, gdybyśmy podstawili za ’a typ int to wrażenie (bool_of_cbool (+)) było by poprawne z punktu widzenia systemu typów, chociaż dodawanie nie jest poprawną reprezentacją wartości Boole’owskiej.

Poprawne typy rozważanych funkcji, które byśmy chcieli uzyskać wymagają by argument był odpowiednio polimorficzny:

• bool_of_cbool : (∀ ’a. ’a -> ’a -> ’a) -> bool

• int_of_cnum : (∀ ’a. (’a -> ’a) -> ’a -> ’a) -> int,

jednak system typów OCamla jest zbyt słaby by wyrazić kwantyfikator uniwersalny w takim miejscu. 
Na szczęście ten problem można obejść używając bardziej zaawansowanych elementów języka, takich jak system modułów (o tym jeszcze będzie), system obiektów (o nim nie będziemy mówić) albo rekordy, których użyjemy
w tym zadaniu. 
W tym celu zdefiniujemy własne typy reprezentujące liczby i wartości Boole’owskie jako rekordy z jednym polem, które jest funkcją polimorficzną.
<br>
```ocaml=
type cbool = { cbool : ’a. ’a -> ’a -> ’a }

type cnum = { cnum : ’a. (’a -> ’a) -> ’a -> ’a }
```
<br>
Teraz nasze reprezentacje liczb i wartości Boole’owskich nie są funkcjami, ale funkcjami opakowanymi w rekord, więc trzeba czasami użyć jawnej konwersji.
Na przykład, aby z wartości n typu cbool utworzyć funkcję należy użyć projekcji n.cbool, natomiast aby polimorficzną funkcję f przekształcić w wartość typu cnum należy utworzyć rekord { cnum = f }. Dokładniej można to zobaczyć w poniższej implementacji funkcji even, która sprawdza czy liczba jest parzysta.
<br>

```ocaml=
let even n =
{ cbool = fun tt ff -> fst (n.cnum (fun (a, b) -> (b, a)) (tt, ff)) }
```
<br>
Zmodyfikuj funkcje z poprzednich dwóch zadań by operowały na typach cbool oraz cnum.

*Uwaga: To zadanie tylko wygląda strasznie, ale w istocie jest bardzo łatwe!*
<br>
