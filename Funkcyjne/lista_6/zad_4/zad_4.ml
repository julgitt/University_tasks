let rec fold_left_cps f acc l cont =
    match l with
    | []    -> cont(acc)
    | hd::tl -> 
    	f acc hd (fun res ->
      		fold_left_cps f res tl cont);;

let fold_left f acc l =
  fold_left_cps (fun acc hd cont -> cont(f acc hd)) 
  		acc 
  		l 
  		(fun res -> res);;
  
let l = [1;2;3];;

let f = (+);;

fold_left f 0 l
(*fold_left_cps (fun acc x cont -> cont(f acc x)) 0 l (fun res -> res)*)
(*f 0 1 (fun res -> fl_cps f res [2;3] (fun res -> res)*)
(* f 0 1 (fun res-> f res 2 (fun res2 -> f res2 3*)
(* f 0 1 (fun res-> f res 2 (fun res2 -> f res2 3 ((fun res3 -> res3) res2*)
(* (fun res-> f res 2 (fun res2 -> f res2 3 ((fun res3 -> res3) res2) f 0 1*)
(* (fun res-> f res 2 (fun res2 -> f res2 3 ((fun res3 -> res3) res2) 1*)
(* f 1 2 (fun res2 -> f res2 3 ((fun res3 -> res3) res2)*)
(* (fun res2 -> f res2 3 ((fun res3 -> res3) res2) f 1 2*)
(* f 3 3 ((fun res3 -> res3) res2)*)
(* ((fun res3 -> res3) 6)*)
(* 6 *)
