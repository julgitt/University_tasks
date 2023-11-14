let rec fix f x = f (fix f) x

type 'a recF = Fold of 'a recF -> 'a;;

let unfold (Fold x) = x

let recFix f x = 
  let fi = fun x y -> f (unfold x x) y
  in fi (fold fi);;
  
let fib_f fib n =
  if n <= 1 
    then n
    else fib (n-1) + fib (n-2)
  let fib = fix fib_f  
  
 (*mutowalny*)
 
 let fix f x =
   let fix_ref1 = ref (fun f x -> failwith "") in
   let fix_ref2 = ref (fun f x -> (!fix_ref1 f) x)in
   fix_ref1 := !fix_ref2;
   !fix_ref2 f x
