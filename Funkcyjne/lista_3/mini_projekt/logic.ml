type formula =
  | Var of string
  | Bottom
  | Implication of formula * formula

let string_of_formula f =
  let rec depth acc f = 
    match f with
    | Var(var) -> var
    | Bottom -> "⊥"    
    | Implication(f1, f2) ->
        let d1 = depth 1 f1
        and d2 = depth 0 f2
        in match acc with
        | 0 -> d1 ^ " → " ^ d2
        | _ -> " ( "^d1^" → " ^d2^" )"
    in
    depth 0 f

let pp_print_formula fmtr f =
  Format.pp_print_string fmtr (string_of_formula f)

let rec cmp f1 f2 =
  let new_f1 = string_of_formula f1
  and new_f2 = string_of_formula f2
  in 
  String.compare new_f1 new_f2

module Formula = struct
  type t = formula
  let compare = cmp
end

module Formulas = Set.Make(Formula)

type theorem = 
  Formulas.t * formula

let assumptions thm =
  Formulas.to_list (fst thm)
 
let consequence thm =
  snd thm
  
let pp_print_theorem fmtr thm =
  let open Format in
  pp_open_hvbox fmtr 2;
  begin match assumptions thm with
  | [] -> ()
  | f :: fs ->
    pp_print_formula fmtr f;
    fs |> List.iter (fun f ->
      pp_print_string fmtr ",";
      pp_print_space fmtr ();
      pp_print_formula fmtr f);
    pp_print_space fmtr ()
  end;
  pp_open_hbox fmtr ();
  pp_print_string fmtr "⊢";
  pp_print_space fmtr ();
  pp_print_formula fmtr (consequence thm);
  pp_close_box fmtr ();
  pp_close_box fmtr ()


  (*Zaimplementuj funkcje by_assumption, imp_i, imp_e oraz bot_e z modułu Logic
odpowiadające regułom wnioskowania. Ich dokładną specyfikację znajdziesz w pliku logic.mli*)

(*
-------(Ax)
{f} ⊢ f  *)
let by_assumption f =
  Formulas.of_list [f] , f

(*
  thm
  Γ ⊢ φ
---------------(→I)
Γ \ {f} ⊢ f → φ 
*)
let imp_i f thm =
  let new_assumptions = Formulas.remove f (fst thm)
  and new_formula = Implication (f, consequence thm) 
  in
  new_assumptions, new_formula

(*
    thm1      thm2
 Γ ⊢ φ → ψ    Δ ⊢ φ 
 ------------------(→E)
 Γ ∪ Δ ⊢ ψ *)
let imp_e th1 th2 =
  let assumptions1, consequence1 = th1 
  and assumptions2, consequence2 = th2 
  in
  match consequence1 with
  | Implication (phi, psi) when cmp phi consequence2 = 0 ->
    Formulas.union assumptions1 assumptions2, psi
  |  _ -> failwith "Invalid input for →E"

(*
 thm
Γ ⊢ ⊥
-----(⊥E)
 Γ ⊢ f 
 *)
let bot_e f thm =
  (fst thm), f

