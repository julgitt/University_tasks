let merge cmp l1 l2 =
  let rec merge_tl cmp acc l1 l2 =
    match (l1, l2) with
        | ([], []) -> acc
        | ([], l) | (l, []) -> (List.rev acc) @ l
        | (hd1::tl1,hd2::tl2) -> if (cmp hd2 hd1)
                                    then merge_tl cmp (hd2 :: acc) l1 tl2
                                    else merge_tl cmp (hd1 :: acc) tl1 l2

let merge2 cmp l1 l2 =
  let rec merge_tl cmp acc l1 l2=
    match (l1, l2) with
    | ([], []) -> acc
    | ([], hd::l) -> merge_tl cmp (hd::acc) l []
    | (hd::l, []) -> merge_tl cmp (hd::acc) l []
    | hd1::tl1, hd2::tl2 -> if cmp hd1 hd2
        then merge_tl cmp (hd1::acc) tl1 l2
        else merge_tl cmp (hd2::acc) l1 tl2
  in merge_tl cmp [] l1 l2

let rec mergesort2 cmp l =
  if ((List.length l) <= 1)
  then l
  else
    let not_cmp = fun a b -> not (cmp a b)
    in merge2 not_cmp 
      (mergesort2 not_cmp (List.hd (halve l))) 
      (mergesort2 not_cmp (List.hd (List.tl (halve l))));; 


mergesort2 (<) [1;8;5;6;3];;
merge2 (<) [1;3;5] [2;4;7;8];;
