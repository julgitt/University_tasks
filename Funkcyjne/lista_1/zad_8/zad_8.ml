type cbool = { cbool : 'a. 'a -> 'a -> 'a } 

let ctrue = {cbool=
               fun x y -> x};;
  
let cfalse = {cbool=
                fun x y -> y};;

let cand p q = {cbool = fun x y -> if p.cbool x y = x then  q.cbool x y else y}
(* less general
let cand p q x y = {cbool = p.cbool (q.cbool (ctrue.cbool x y) (cfalse.cbool x y)) (cfalse.cbool x y)}*)

let cor p q = {cbool = fun x y -> if p.cbool x y = x then x else q.cbool x y} 
             
              
let cbool_of_bool (p : bool) =  if p 
                                then ctrue 
                                else cfalse}

let bool_of_cbool p =
  p.cbool true false
  
  
type cnum = { cnum : 'a. ('a -> 'a) -> 'a -> 'a }
    
let zero = {cnum = fun f z -> z}

let succ num = {cnum = fun f z -> f (num.cnum f z)}

let add num1 num2 = {cnum = fun f z -> num1.cnum f (num2.cnum f z)}

let mult num1 num2 = {cnum = fun f z -> num1.cnum (num2.cnum f) z}
                       
let is_zero num = {cbool = fun f z -> num.cnum (fun _ -> f) z}

let rec cnum_of_int a = if a = 0 then zero else succ(cnum_of_int (a - 1))

let rec int_of_cnum a = a.cnum (fun x -> x + 1) 0
