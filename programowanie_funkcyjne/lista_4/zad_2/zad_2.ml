type 'a zlist =
  'a list * 'a list

let of_list l = ([],l);;

let to_list (l, r) = 
  List.rev_append l r;;

let elem (_, r) =
  match r with
  | [] -> None
  | hd :: _ -> Some hd

let move_left (l,r) = 
  match l with 
  | [] -> (l,r)
  | hd::tl -> (tl, hd::r);;
  
let move_right (l,r) =
  match r with 
  | [] -> (l,r)
  | hd::tl -> (hd::l, tl);;

let insert x (l, r) = 
  (x::l, r);;

let remove (l,r) =
  match l with
  | [] -> failwith "Cannot remove element from an empty list"
  | hd::tl -> (tl,r);;
