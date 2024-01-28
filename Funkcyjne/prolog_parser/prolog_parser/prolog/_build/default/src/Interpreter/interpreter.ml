open Ast
open Stack.BacktrackRefMonad
open Printer

(*          UNIFIKACJA               *)

let rec unify t1 t2 =
  let rec contains_var x t =
    match view t with
    | Var (_, y) -> x = y
    | Sym(_, ts) -> List.exists (contains_var x) ts
  in

  let rec unify_lists ts1 ts2 =
    match ts1, ts2 with
    | [], [] -> return true
    | t1 :: rest1, t2 :: rest2 ->
      let* is_unified = unify t1 t2 in
      if is_unified then unify_lists rest1 rest2
      else 
        return false
    | _ -> return false
  in

  match view t1, view t2 with
  | Var (_, x), Var (_, y) when x = y -> return true
  | Var (name, x), t |  t, Var (name, x)->
    if contains_var x t then return false
    else push_substitution (name, t)
  | Sym(f1, ts1), Sym(f2, ts2) when f1 = f2 && List.length ts1 = List.length ts2 ->
    unify_lists ts1 ts2
  | _ -> return false


(*          SEMANTYKA               *)

let split_clause c = 
  match c with
  | Fact t ->
    let h = t in 
    (h, []) 
  | Rule (t, ts) ->
      let h = t in
      let b = ts in 
      (h, b)
          

let select_clause () = 
  let* predicate_base = get_clauses () in
  match predicate_base with
  | [] -> return None
  | c :: rest -> 
    let* _ = set_clauses rest in
    return (Some c)


let rec solve goals =
  let* _ = set_goals goals in
  match goals with
  | []      -> return true
  | g :: gs ->
    let* cl = select_clause () in
    match cl with
    | Some c -> 
      let (h, b) = split_clause c in
      let* t = unify h g in
      if t then (
          let* () = set_substitutions () in
          let* () = restore_clauses () in
          solve (b @ gs)
      ) else (
          let* _ = restore_substitutions () in 
          solve goals )
    | None ->
      let* new_goals = backtrack_goals () in
      match new_goals with
      | [] -> return false
      | _  ->  solve new_goals