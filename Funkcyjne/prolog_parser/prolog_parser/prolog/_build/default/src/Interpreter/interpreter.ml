open Ast
open BacktrackStateMonad.BacktrackStateMonad
open Printer

(*          UNIFIKACJA               *)

let rec unify t1 t2 =
  let rec contains_var x t =
    match view t with
    | Var (_, y)  -> x = y
    | Sym (_, ts) -> List.exists (contains_var x) ts
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
  | Var (n1, x), Var (n2, y) when x = y -> 
    push_substitution (n1, Some (Var(n2,y)));
  | Var (n, x), t |  t, Var (n, x)->
    if contains_var x t then return false
    else push_substitution (n, Some t)
  | Sym(h1, ts1), Sym(h2, ts2) when h1 = h2 && List.length ts1 = List.length ts2 ->
    unify_lists ts1 ts2
  | _ -> return false


(*          SEMANTYKA               *)

let rec renameVariables t = 
  match t with
  | Var(name, x) ->  
    (match !x with
    | None     -> Var(name ^ "`", ref None)
    | Some y   -> Var(name, ref (Some (renameVariables y)))
    )
  | Sym(f, ts) -> Sym(f, (List.map renameVariables ts))


let refresh_clause c = 
  match c with
  | Fact t ->
    let h = renameVariables t in
    let b = [] in 
    (h, b) 
  | Rule (t, ts) ->
    let h = renameVariables t in
    let b = List.map renameVariables ts in 
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
    let* clause = select_clause () in
    match clause with
    | Some c -> 
      let (h, b) = refresh_clause c in
      let* is_unified = unify h g in
      if is_unified then
          let* () = set_substitutions () in
          let* () = restore_clauses () in
          solve (b @ gs)
        else
          let* _ = restore_substitutions () in 
          solve goals
    | None ->
      let* new_goals = backtrack_goals () in
      match new_goals with
      | [] -> return false
      | _  ->  solve new_goals