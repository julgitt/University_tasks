
open Ast;;

let rec view t =
  match t with
  | Var (_, x) ->
    begin match !x with
    | None -> t
    | Some t -> view t
    end
  | _ -> t

let rec print_terms q =
  match q with
  | [] -> print_string ""
  | [t] -> 
        (match view t with 
        | Var(name, _) -> 
              print_string name;
        | Sym(name, []) -> 
              print_string name;
        | Sym(name, xs) -> 
              print_string name;
              print_string "(";
              print_terms xs;
              print_string ")";
        );
  | t :: ts  -> 
        print_terms [t];
        print_string ", ";
        print_terms ts
        
       


let rec print_clauses p =
  match p with
  | [] -> ()
  | c :: cs -> 
        (match c with 
        | Fact t -> 
              print_terms [t];
        | Rule (t, ts) -> 
              print_terms [t];
              print_string " :- ";
              print_terms ts;
        );
        print_endline ".";
        print_clauses cs