type 'a dllist = 'a dllist_data lazy_t
and 'a dllist_data = {
  prev : 'a dllist;
  elem : 'a;
  next : 'a dllist;
}

let prev dlist =
  let {prev; elem; next} = Lazy.force dlist 
  in prev

let next dlist =
  let {prev; elem; next} = Lazy.force dlist 
  in next

let elem dlist =
  let {prev; elem; next} = Lazy.force dlist in
  elem


let of_list lst : 'a dllist = 
  match l with
  | [] -> failwith "Empty list"
  | [x] ->
    let rec singleton_dllist = lazy {
      prev = singleton_dllist;
      elem = x;
      next = singleton_dllist;
    }
    in singleton_dllist
  | hd :: tl ->
    let rec next_node last_node prev l =
      match l with
      (* jesteśmy na końcu *)
      | hd1::hd2::[] 	-> lazy {
          prev = prev;
          elem = hd1;
          next = last_node;
        }
      (* jesteśmy w środku *)
      | hd::tl 	-> 
    	  let rec node = lazy {
    	    prev = prev;
          elem = hd;
          next = next_node last_node node tl;
          }
    	  in node
    in 
    let rec get_last_node first_node prev l = 
      match l with
      (* znaleźliśmy ostatni element*)
      | hd1::hd2::[] -> {
        prev = prev;
        elem = hd2;
        next = first_node;
        }
      (* jesteśmy gdzieś w środku listy - szukamy dalej *)
      | hd::tl       -> 
        get_last_node first_node (next prev) tl
    in
    let rec first_node = 
      let last_node = lazy(get_last_node first_node first_node l) 
      in 
      lazy {
        prev = last_node;
        elem = hd;
        next = next_node last_node first_node tl
      }
    in
    first_node;;
   
  
  let l = [7;8;9;10];;
  
  let dl = of_list l;;