
(*Jaki jest typ wyrażenia fun x -> x?*) 

'a -> 'a

(*Napisz wyrażenie, którego wartością też jest funkcja identycznościowa, ale które ma typ int -> int.*)

fun f x = x + 0

(*Napisz wyrażenia, których typami są:*)
(* (’a -> ’b) -> (’c -> ’a) -> ’c -> ’b*)

fun f g x -> f (g x)

(*’a -> ’b -> ’a*)

fun x y -> x

(*’a -> ’a -> ’a*)

fun f x y = if x == y then x else y;;

(*Czy potrafisz napisać wyrażenie typu ’a?*)

(*Nie, jest to typ polimorficzny, który może oznaczać każdy typ, ale nie moge go bezpośrednio stworzyć.*)


