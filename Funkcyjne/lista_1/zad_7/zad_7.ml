(*Wartościami zamkniętych wyrażeń typu (’a -> ’a) -> ’a -> ’a są wszystkie funkcje postaci (f, x) → f^n (x) dla dowolnej liczby naturalnej n, więc można użyć tego typu do reprezentacji liczb naturalnych. 
Zdefiniuj liczbę zero, operację następnika, operacje dodawania i mnożenia, funkcję sprawdzającą, czy dana liczba jest zerem, a także konwersje między naszą reprezentacją a wbudowanym typem liczb całkowitych (nie przejmuj się liczbami ujemnymi):*)

(*zero : (’a -> ’a) -> ’a -> ’a*)

let zero f z = z


(*succ : ((’a -> ’a) -> ’a -> ’a) -> (’a -> ’a) -> ’a -> ’a*)


(*('a -> 'b) -> 'c -> 'a) -> ('a -> 'b) -> 'c -> 'b*)
let succ num =
    fun f z -> f (num f z);;
    

(*add, mul : ((’a -> ’a) -> ’a -> ’a) ->
((’a -> ’a) -> ’a -> ’a) -> (’a -> ’a) -> ’a -> ’a*)

let add num1 num2 = 
        fun f z -> (num1 f (num2 f z));;

(*('a -> 'b -> 'c) -> ('d -> 'a) -> 'd -> 'b -> 'c*)
let mul num1 num2 = 
        fun f z -> (num1 (num2 f)) z;;
        
(* rozpisanie mul: 
num1 = 2, num2 = 2 = succ(succ zero)*)
(*num1 f = succ(succ zero) -> num 1 = f(f zero) = succ(succ (succ (succ zero)))*)

(*is_zero : ((’a -> ’a) -> ’a -> ’a) -> ’a -> ’a -> ’a*)
let is_zero num  = num (
    fun _ -> cfalse) ctrue;;

(*cnum_of_int : int -> (’a -> ’a) -> ’a -> ’a*)
let rec cnum_of_int (a : int) = if a = 0 then zero else succ(cnum_of_int (a - 1))

(*int_of_cnum : ((int -> int) -> int -> int) -> int*)
let int_of_cnum (a : ((int -> int) -> int -> int)) 
    = a (fun a -> a + 1) 0;; 

(*W funkcji is_zero typ wyniku (’a -> ’a -> ’a) to reprezentacja wartości Boole’owskich z poprzedniego zadania.
Zastanów się, czemu typy niektórych z powyższych funkcji znalezione przez algorytm rekonstrukcji typów różnią się od podanych powyżej.
*Wskazówka: podobnie jak w poprzednim zadaniu o takich liczbach można myśleć jak o funkcjach, które biorą jako parametry reprezentację następnika i zera i z nich budują odpowiednią wartość.*)

