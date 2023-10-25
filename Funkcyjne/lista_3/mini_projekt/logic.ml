

type formula =
  | Var of string
  | FalseVar
  | Implication of formula * formula

  let string_of_formula f =
    let rec depth acc f = 
      match f with
      | Var(var) -> var
      | FalseVar-> "⊥"    
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

type theorem = 
  | Ax of formula                  (* Axiom: {φ} ⊢ φ *)
  | ImplIntro of theorem           (* Implication Introduction: Γ ⊢ φ --> Γ \ {ψ} ⊢ ψ → φ *)
  | ImplElim of theorem * theorem  (* Implication Elimination: Γ ⊢ φ → ψ, ∆ ⊢ φ --> Γ ∪ ∆ ⊢ ψ *)
  | FalseElim of theorem           (* False Elimination: Γ ⊢ ⊥, Γ ⊢ φ *)

let assumptions thm =
  match thm with
  | Ax _ -> []                     (* Axiom has no assumptions *)
  | ImplIntro t -> assumptions t  (* Assumptions of Implication Introduction *)
  | ImplElim (l_proof, _) -> assumptions l_proof  (* Assumptions of Implication Elimination *)
  | FalseElim premises -> premises  (* Assumptions of False Elimination *)

let consequence thm =
  match thm with
  | Ax formula -> formula           (* Consequence of Axiom is the formula itself *)
  | ImplIntro _ -> failwith         "Invalid: An assumption cannot be a consequence."
  | ImplElim (_, r_proof) -> consequence r_proof  (* Consequence =of Implication Elimination *)
  | FalseElim _ -> FalseVar         (* Consequence of False Elimination is FalseVar *)

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
let by_assumption f =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let imp_i f thm =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let imp_e th1 th2 =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let bot_e f thm =
  (* TODO: zaimplementuj *)
  failwith "not implemented"
