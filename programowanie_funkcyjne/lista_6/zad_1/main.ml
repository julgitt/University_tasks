type ('a, 'b) format = (string -> 'a) -> (string -> 'b);;

(*: string -> ('a,'a) format*)
let lit s1  =
	fun cont s2 -> cont(s2 ^ s1);; 
	
(*: (int -> 'a,'a) format*)	
let int cont =
	fun s x -> cont(s ^ string_of_int x);;
	
(*: (str -> 'a,'a) format *)	
let str cont =
	fun s x -> cont(s ^ x);;

let (^^) f1 f2 = 
	fun cont -> f1 (f2 cont);;


let ksprintf text cont = text cont "";;

let sprintf text = ksprintf text (fun x -> x);;

sprintf (lit "Ala ma " ^^ int ^^ lit " kot" ^^ str ^^ lit ".");;

(*fun cont -> lit "Ala ma " (int (lit " kot" (str (lit "." cont))))*)
(*ksprintf (fun cont -> lit "Ala ma " (int (lit " kot" (str (lit "." cont))))) (fun  x -> x)*)
(*lit "Ala ma " (int (lit " kot" (str (lit "." fun x->x)))) "" *)
(*lit "Ala ma " (int (lit " kot" (str fun x->x "."))) ow *)
(*lit "Ala ma " (int (lit " kot" fun x->x "ow."))*)
(*lit "Ala ma " (int (fun x->x " kotow.")) 5*)
(*lit "Ala ma " (fun x->x "5 kotow.")*)
(* fun x -> x "Ala ma 5 kotow."*)
(*"Ala ma 5 kotow."*)

