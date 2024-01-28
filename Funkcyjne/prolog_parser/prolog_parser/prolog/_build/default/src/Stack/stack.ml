(*    NAWRACANIE I MUTOWALNY STAN    *)  
open Ast;;
open Printer;;

module BacktrackRefMonad : sig
  type state
  type 'a t
  
  (* Stack operations *)
  val is_empty : unit -> bool t 
  val get      : unit -> state t
  val set      : state -> unit t
  val pop      : unit -> state t 

  (* Clearing/Initialising *)
  val init_state  : clause list -> unit t

  (* State getters/setters *)
  val set_goals   : term list -> unit t
  (*val get_goals   : unit -> term list t*)

  val set_clauses   : clause list -> unit t
  val get_clauses   : unit -> clause list t
  val restore_clauses : unit -> unit t
  
  val set_substitutions : unit -> unit t 
  val get_substitutions : unit -> (variable * term) list t
  val push_substitution : (variable * term) -> bool t
  val restore_substitutions  : unit -> unit t

  (* Backtracking *)
  val backtrack_goals : unit -> term list t
  
  (* Monad functions *)
  val return : 'a -> 'a t

  val (let*) : 'a t -> ('a -> 'b t) -> 'b t
  val (let+) : 'a t -> ('a -> 'b) -> 'b t

  val run : unit -> 'a t -> 'a
end = struct
  module IntMap = Map.Make(Int)

  type state = {
    program            : clause list;
    substitutions      : (variable * term) list; 
    clauses            : clause list;
    goals              : term list;
  }

  type 'a t = state IntMap.t -> 'a * state IntMap.t
  
  let _temp_substitutions : ((variable * term) list ref) = ref [] 

  let _make_state p s c g =
    {
      program       = p;
      substitutions = s;
      clauses       = c;
      goals         = g;
    }


(*        Stack operations      *)

  let is_empty () map =
    let empty = IntMap.is_empty map in 
    (empty, map)

  let get () map = 
    let key  = (IntMap.cardinal map) - 1 in
    let v    = IntMap.find key map in
    (v, map)
  
  let set v map = 
    let key     = IntMap.cardinal map in
    let new_map = IntMap.add key v map in
    ((), new_map)

  let pop () map = 
    let key     = (IntMap.cardinal map) - 1 in
    let (v, _)  = get () map in
    let new_map = IntMap.remove key map in
    (v, new_map)
    
  let _update new_state map =
    let (_, new_map) = pop () map in
    let (_, new_map) = set new_state new_map in 
    ((), new_map)
  

(*        Initialising      *)
  let init_state program _ =
    let new_state = (_make_state program [] program []) in
    let new_map   = IntMap.singleton 0 new_state in
    ((), new_map)


(*        State getters       *)
  let _get_program () map = 
    let (state, _) = get () map in
    (state.program, map)

  let _get_goals () map =
    let state, map = get () map in
    (state.goals, map)
  
  let get_clauses () map =
    let (state, map) = get () map in
    (state.clauses, map)

  let get_substitutions () map =
    let (state, _) = get () map in
    (state.substitutions, map)


(*      Goals       *)
  let _update_goal_variables gs map =
    match gs with
    | Var(n, x) :: _ when !x = None ->
      let subs = fst (get_substitutions () map) in
      List.iter (fun (name, term) -> 
        if name = n then x := Some term) subs
      
    | _ -> ()


  let set_goals goals map =                          
    let new_state = _make_state (fst (_get_program () map))
                                (fst (get_substitutions () map))
                                (fst (get_clauses () map))
                                goals    
    in                       
    let ((), new_map) = _update new_state map in
    _update_goal_variables goals new_map;
    ((), new_map)
  
(*        substitutions       *)
  let set_substitutions () map =
    let old_subs = (fst (get_substitutions () map)) in
    let new_subs = !_temp_substitutions in
    let all_subs = new_subs @ old_subs in
    let new_state = _make_state (fst (_get_program () map))
                                all_subs
                                (fst (get_clauses () map))
                                (fst (_get_goals () map))
    in
    _temp_substitutions := [];
    set new_state map


  let restore_substitutions () map =
    _temp_substitutions := [];
    ((), map)
  

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


(*        clauses         *)
  let set_clauses cs map =
    let new_state = _make_state (fst (_get_program () map))
                                (fst (get_substitutions () map))
                                cs
                                (fst (_get_goals () map))
    in
    _update new_state map


  let restore_clauses () map =
    let new_state = _make_state  (fst(_get_program () map))
                                (fst(get_substitutions () map))
                                (fst(_get_program () map))
                                (fst(_get_goals () map))
    in
    _update new_state map


(*        Backtracking      *)
  let backtrack_goals () map =
    let (_, map)    = pop () map in
    let (empty, _)  = is_empty () map in
    if (empty)
      then ([], map)
      else
        let (prev_goals, _) = _get_goals () map in
        (prev_goals, map)
    

(*      Monads operators      *)
  let return x map = (x, map)
  
  let (let*) m f map = m map |> fun (a, map) -> f a map

  let (let+) m f map = m map |> fun (a, map) -> (f a, map)
  
  let run () computation =
    let res, _ = computation IntMap.empty in
    res

end
