open Ast;;
open Printer;;

module State = struct

  include Stack

  type state = {
    program       : clause list;
    substitutions : (variable * term option) list; 
    clauses       : clause list;
    goals         : term list;
  }

    let _make_state p v c g =
    {
      program       = p;
      substitutions = v;
      clauses       = c;
      goals         = g;
    }

  let _print_state s =
    print_endline "Klauzule:";
    print_clauses (s.clauses);
    print_endline "\nTermy";
    print_terms (s.goals);
    print_endline "\nProdukcje";
    print_results (s.substitutions);
    print_endline "\n";
    ()
      
  let _temp_substitutions : ((variable * term option) list ref) = ref [] 



  (*        Initialising      *)
  let _init_state program variables =
    _make_state program variables program []

  (*        State getters       *)
  let _get_program map = 
    let (state, _) = Stack.get () map in
    state.program

  let _get_goals map =
    let state, _ = Stack.get () map in
    state.goals

  let get_clauses () map =
    let (state, _) = Stack.get () map in
    (state.clauses, map)

  let _get_original_variables map =
    let (state, _) = Stack.get () map in
    state.substitutions

  let get_substitutions () map =
    let variables = _get_original_variables map in
    let substitutions = List.filter (fun (_, term) -> 
                                      term <> None) 
                                    variables
    in
    (substitutions, map)

  (*        substitutions       *)

  let set_substitutions () map =
    let original_variables = _get_original_variables map in
    let new_subs = !_temp_substitutions
    in
    let find_substitution variable =
      List.assoc_opt variable new_subs
    in
    let apply_substitution (name, x) =
      match x with
      | None -> (
          match find_substitution name with
          | Some new_term -> (name, new_term)
          | None -> (name, x)
        ) 
      | _ -> (name, x)
    in
    let new_variables = List.map apply_substitution original_variables;
    in  
    let new_state = _make_state (_get_program map)
                                new_variables
                                (fst (get_clauses () map))
                                (_get_goals map)
    in
    Stack.push new_state map
  
  
  let _has_substitution_pair pair substitutions =
    List.exists (fun (name, term) -> 
      name = (fst pair) && not (term = (snd pair))
      ) substitutions


  let _has_substitution_name name subs =
   List.exists (fun (n,_) -> n = name) subs
  
  
  let push_substitution pair map =
    let temp_subs = !_temp_substitutions in
    let subs = fst (get_substitutions () map) in
    let all_subs = temp_subs @ subs 
    in
    if _has_substitution_pair pair all_subs then 
      (false, map) 
    else if _has_substitution_name (fst pair) all_subs then 
      (true, map)
    else begin
      _temp_substitutions := pair :: temp_subs;
      (true, map)
    end

  let restore_substitutions () map =
    _temp_substitutions := [];
    ((), map)

  
  (*let _restore_substitutions () map =
    let original_variables = (_get_original_variables map) in
    _temp_substitutions := [];
    let apply_substitution (name, _) = (name, None) in
    let new_subs = List.map apply_substitution original_variables
    in
    let new_state = _make_state (_get_program map)                                
                                new_subs
                                (fst(get_clauses () map))
                                (_get_goals map)
    in
    Stack._update new_state map*)


  (*      Goals       *)
  let rec _update_goals_variables goals substitutions =
    match goals with
    | [] -> ()
    | Var (n, x) :: gs when !x = None ->
      List.iter (fun (name, term) ->
        if name = n then x := term
      ) substitutions;
      _update_goals_variables gs substitutions
    | Sym (_, ts) :: gs -> _update_goals_variables (ts @ gs) substitutions
    | _ :: gs -> _update_goals_variables gs substitutions


  let set_goals goals map =                          
    let new_state = _make_state (_get_program map)
                                (_get_original_variables map)
                                (fst (get_clauses () map))
                                goals    
    in                       
    let ((), new_map) = Stack._update new_state map in
    let substitutions = fst (get_substitutions () new_map) @ !_temp_substitutions in
    _update_goals_variables goals substitutions;
    restore_substitutions () new_map


  (*        clauses         *)
  let set_clauses cs map =
    let new_state = _make_state (_get_program map)
                                (_get_original_variables map)
                                cs
                                (_get_goals map)
    in
    Stack._update new_state map

  let restore_clauses () map =
    let new_state = _make_state (_get_program map)
                                (_get_original_variables map)
                                (_get_program map)
                                (_get_goals map)
    in
    Stack._update new_state map

  end
