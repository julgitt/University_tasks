(*Ile różnych wartości mają zamknięte wyrażenia typu ’a -> ’a -> ’a, których obliczenie nie wywołuje żadnych efektów ubocznych (tj. które zawsze kończą działanie, nie wywołują wyjątków, nie używają operacji wejścia/wyjścia itp.)? Okazuje się, że jest ich dokładnie tyle, ile potrzeba, by reprezentować za ich pomocą wartości logiczne prawdy i fałszu! Zdefiniuj odpowiednie wartości ctrue i cfalse typu ’a -> ’a -> ’a.*)


(*a -> b -> a*)
let ctrue =
  fun x y -> x;;
  
let cfalse =
  fun x y -> y;;

(*oraz funkcje o podanych niżej sygnaturach implementujące operacje koniunkcji i alternatywy oraz konwersji między naszą reprezentacją a wbudowanym typem wartości logicznych.

cand, cor: (’a -> ’a -> ’a) -> (’a -> ’a -> ’a) -> ’a -> ’a -> ’a*)

(* ('a -> 'b -> 'c) -> ('b -> 'b -> 'a) -> 'b -> 'b -> 'c *)
let cand p q x y =
  p (q (ctrue x y) (cfalse x y)) (cfalse x y);;

(* ('a -> 'b -> 'c) -> ('a -> 'a -> 'b) -> 'a -> 'a -> 'c *)
let cor p q x y = p (ctrue x y) (q (ctrue x y) (cfalse x y)) 

(* 'a - (ctrue x y) *)
(* 'b - zwracane przez q *)
(* 'c - zwracane przez p *)
(* p i q są typu ctrue / cfalse, ale powyżej nie jest to narzucone, może to być jakiś inny typ, który nie wiadomo jaki typ zwraca )


cbool_of_bool: bool -> ’a -> ’a -> ’a*)

let cbool_of_bool (p : bool) = 
    if p 
    then ctrue 
    else cfalse;;


(*bool_of_cbool: (bool -> bool -> bool) -> bool*)

let bool_of_cbool (p : bool -> bool -> bool) =
        p true false;;


(*Zastanów się, czemu typy niektórych z powyższych funkcji znalezione przez algorytm rekonstrukcji typów różnią się od podanych powyżej.

*Wskazówka: o takiej reprezentacji wartości logicznych można myśleć jak o funkcjach, które biorą dwa parametry: reprezentację prawdy i reprezentację fałszu i wybierają jedną z nich. 
Implementując operacje cand i cor weź wszystkie argumenty.*)

