type 'a my_lazy = 'a lazy_data ref
and 'a lazy_data = 
| Ready    of 'a
| Deffered of (unit -> 'a)
| Currently_Computing ;;

let force lazy_val =
  match !lazy_val with
  | Currently_Computing -> failwith "Value is currently computing"
  | Ready x 	-> x
  | Deffered f 	-> 
    lazy_val := Currently_Computing;
    let value = f () in
    lazy_val := Ready value;
    value;;

let fix f = 
  let rec lazy_comp = 
    ref (Deffered (fun () -> f lazy_comp)) 
  in lazy_comp;;


type 'a llist = 'a node my_lazy
and 'a node =
| Nill
| Cons of 'a * 'a llist;;

let stream_of_ones = fix (fun stream_of_ones -> Cons(1,stream_of_ones));;
fix (fun l -> force l);;
force (fix (fun l -> force l));;
