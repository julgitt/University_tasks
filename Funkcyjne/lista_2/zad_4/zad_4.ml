let rec merge cmp l1 l2 =
  match (l1, l2) with
  | ([], l) -> l
  | (l, []) -> l
  | (h1::t1, h2::t2) ->
    if cmp h1 h2 
    then h1 :: merge cmp t1 l2
    else h2 :: merge cmp l1 t2;;
```
```ocaml=
let merge cmp l1 l2 =
  let rec merge_tl cmp acc l1 l2 =
    match (l1, l2) with
        | ([], []) -> acc
        | ([], l) | (l, []) -> (List.rev acc) @ l
        | (hd1::tl1,hd2::tl2) -> if (cmp hd2 hd1)
                                    then merge_tl cmp (hd2 :: acc) l1 tl2
                                    else merge_tl cmp (hd1 :: acc) tl1 l2
  in merge_tl cmp [] l1 l2

let halve l =
  let rec help l1 l2 ptr =
    match ptr with
      | [] | _::[] -> [List.rev l1; l2]
      | _::_::tl2 -> help ((List.hd l2) :: l1) (List.tl l2) tl2
  in help [] l l;;

 let rec mergesort cmp l =
    if ((List.length l) <= 1)
        then l
        else merge cmp
            (mergesort cmp (List.hd (halve l)))
            (mergesort cmp (List.hd (List.tl (halve l))))
