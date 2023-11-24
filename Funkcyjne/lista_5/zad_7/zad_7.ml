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
    let value = f () in
    lazy_val := Ready value;
    value;;

let fix f = 
  let rec lazy_comp = 
    ref (Deffered (fun () -> f lazy_comp)) 
  in lazy_comp;;

type 'a llist = 'a node my_lazy
and 'a node =
| Nil
| Cons of 'a * 'a llist

let rec nth n xs =
  match force xs with
  | Nil -> raise Not_found
  | Cons(x, xs) ->
    if n = 0 then x
    else nth (n-1) xs

let rec nats_from n = 
  fix (fun _ -> Cons(n, nats_from (n+1)))

