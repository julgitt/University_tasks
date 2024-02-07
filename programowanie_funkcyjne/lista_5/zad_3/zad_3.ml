(* Typ reprezentujący ułamek jako parę liczb całkowitych *)
type fraction = int * int;;

(* Definicja leniwego drzewa dla liczb wymiernych dodatnich *)
type lazy_tree =
  | Node of fraction * (unit -> lazy_tree) * (unit -> lazy_tree);;

(* Funkcja tworząca drzewo wszystkich liczb wymiernych dodatnich *)
let rec create_rational_tree a b c d =
  Node ((a + c, b + d),
        (fun () -> create_rational_tree a b (a + c) (b + d)),
        (fun () -> create_rational_tree (a + c) (b + d) c d));;

let first t =
  match t with
  | Node(el, f, s) -> f();;


let second t =
  match t with
  | Node(el, f, s) -> s();;