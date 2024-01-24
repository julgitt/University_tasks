open Ast
open Stack.BacktrackRefMonad
open Helper


let initial_state = {
  program       = [];
  substitutions = []; 
  clauses       = [];
  goals         = [];
}

(*          UNIFIKACJA               *)


let rec contains_var x t =
  match view t with
  | Var (_, y) -> x == y
  | Sym(_, ts) -> 
    List.exists (contains_var x) ts 

let rec unify t1 t2 =
  let rec unify_all ts1 ts2 =
    match ts1, ts2 with
    | [], [] -> return true
    | t1 :: rest1, t2 :: rest2 ->
      let* result = unify t1 t2 in
      if result then
        unify_all rest1 rest2
      else
        return false
    | _ -> return false;
  in
  match view t1, view t2 with
  | Var (_, x), Var (_, y) when x == y -> return true
  | Var (name, x), t | t, Var (name, x) ->
    (match (contains_var x t ) with 
    | true ->  return false;
    | false ->
        (*x := Some t;*)
        let* () = push_substitution (name, t) in
        let* v = get () in
        let* () = set v in
        return true;
    )
  | Sym(f1, ts1), Sym(f2, ts2) ->
    if f1 = f2 && List.length ts1 = List.length ts2
    then unify_all ts1 ts2
    else return false



(*          SEMANTYKA               *)

let rec changeVarNames t = 
  match t with
  | Var(name, x) ->  
    (match !x with
    | None     -> Var(name ^ "`", ref None)
    | Some y   -> Var(name, ref (Some (changeVarNames y)))
    )
  | Sym(f, ts) -> Sym(f, (List.map changeVarNames ts))


let select_clause () = 
  let* predicate_base = get_clauses () in
  match predicate_base with
  | [] -> 
    return None
  | c :: rest -> 
    let* _ = set_clauses rest in
    return (Some c)


let refresh_clause c = 
  match c with
  | Fact t ->
    let h = changeVarNames t in
    let b = [] in 
    (h, b) 
  | Rule (t, ts) ->
    let h = changeVarNames t in
    let b = List.map changeVarNames ts in 
    (h, b)


let rec solve goals =
  let* _ = set_goals goals in
  match goals with
  | [] -> 
    return ()
  | g :: gs ->
    let* cl = select_clause () in
    match cl with
    | Some c -> 
        let (h, b) = refresh_clause c in
        let* t = unify h g in
        if (t) 
          then (
            let* () = reset_clauses () in
            solve (b @ gs)
          )
          else (
            solve goals
          )  
    | _ ->
        let* new_goals = backtrack_goals () in
        solve new_goals