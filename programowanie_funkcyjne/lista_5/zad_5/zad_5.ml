type 'a dllist = 'a dllist_data lazy_t
and 'a dllist_data = {
  prev : 'a dllist;
  elem : 'a;
  next : 'a dllist;
}

let prev dlist =
  let {prev; elem; next} = Lazy.force dlist in
  prev

let next dlist =
  let {prev; elem; next} = Lazy.force dlist in
  next

let elem dlist =
  let {prev; elem; next} = Lazy.force dlist in
  elem

(* Function generating an infinite lazy list of integers *)
let integers =
  let rec create_nodes prev elem next =
    let current_node = lazy {
      prev = prev;
      elem = elem;
      next = next;
    }
    in
    lazy {
      prev = create_nodes prev (elem - 1) current_node;
      elem = elem;
      next = create_nodes current_node (elem + 1) next;
    }
  in
  let rec start = lazy {
    prev = start;
    elem = 0;
    next = start;
  }
  in create_nodes start 0 start
