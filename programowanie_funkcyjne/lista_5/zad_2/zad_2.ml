let rec fix f x = f (fix f) x

type 'a recF = Fold of ('a recF -> 'a);;

let unfold (Fold x) = x;;

(* Y = lambda f.(lambda x. f(x x))(lambda x. f(x x)).*)

(*Beta redukcja 

Y g = (...) g
    = (lambda x. g(x x)) (lambda x. g(x x)) 
    = g ((lambda x. g(x x)) (lambda x. g(x x)))
    = g (Y g)   
*)

(* fi (Fold fi)
(fun x y -> f (unfold x x) y) (Fold (fun x y -> f (unfold x x) y))
(fun y -> f ((fun x y -> f (unfold x x) y) (Fold (fun x y -> f (unfold x x) y))) y)
f ((fun x y -> f (unfold x x) y) (Fold (fun x y -> f (unfold x x) y)))
f (fi (Fold fi))...
*)

let recFix f x = 
  let fi = fun x y -> f (unfold x x) y
  in fi (Fold fi);;
  
let fib_f fib n =
  if n <= 1 
    then n
    else fib (n-1) + fib (n-2)
  let fib = fix fib_f  
  
 (*mutowalny*)
 (*fix_ref1 = fun f x -> (fix_ref1 f) x*)
 (*fix_ref2 = (fun f x -> (!fix_ref1 f) x)
 fix_ref2 f x = fix_ref1 f x
  *)
 let fix f x =
   let fix_ref1 = ref (fun f x -> failwith "") in
   let fix_ref2 = ref (fun f x -> (!fix_ref1 f) x)in
   fix_ref1 := !fix_ref2;
   !fix_ref2 f x
