(*
   Zadanie 8 (3p). Rozważmy następujący typ danych opisujący pewien podzbiór typów skończonych.
type _ fin_type =
| Unit : unit fin_type
| Bool : bool fin_type
| Pair : ’a fin_type * ’b fin_type -> (’a * ’b) fin_type
Zaimplementuj funkcję all_values: ’a fin_type -> ’a Seq.t, która dla podanego typu 
zwraca wszystkie jego elementy. 
Na przykład, wywołanie all_values (Pair(Unit, Bool)) powinno zwrócić sekwencję
dwóch par: ((), true) oraz ((), false).
*)

type _ fin_type = 
| Unit : unit fin_type
| Bool : bool fin_type
| Pair :  'a fin_type * 'b fin_type -> ('a * 'b) fin_type;;

let rec all_values : type a. a fin_type -> a Seq.t = 
  fun ft -> (
    match ft with
    | Unit -> Seq.return ()
    | Bool -> Seq.cons true (Seq.return false)
    | Pair(x,y) -> 
      let seq_x = all_values x
      in 
      let seq_y = all_values y
      in 
      Seq.flat_map (fun x -> (Seq.map (fun y -> (x, y)) seq_y)) seq_x)
  ;;
  
let values = all_values (Pair(Unit, Bool));;
let values2 = all_values (Pair(Pair(Bool, Bool), Bool));;
List.of_seq values;;
List.of_seq values2;;
