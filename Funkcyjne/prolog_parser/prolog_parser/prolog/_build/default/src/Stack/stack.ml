(*    NAWRACANIE I MUTOWALNY STAN    *)  
open Ast;;
open Helper;;

module BacktrackRefMonad : sig
  type goal = 
  | Variable of variable
  | Symbol of symbol * goal list

  type state = {
    program       : clause list;
    substitutions : (variable * term) list; 
    clauses       : clause list;
    goals         : goal list;
  }
  type 'a t
  
  (* Stack operations *)
  val is_empty : unit -> bool t 
  val get : unit -> state t
  val set : state -> unit t
  val pop : unit -> state t 

  (* Clearing/Initialising *)
  val init_state  : clause list -> unit t
  val clear_state : unit -> unit t

  (* State getters/setters *)
  val set_goals   : term list -> unit t
  val get_goals   : unit -> term list t

  val set_clauses   : clause list -> unit t
  val reset_clauses : unit -> unit t
  val get_clauses   : unit -> clause list t
  
  val get_substitutions : unit -> ((variable * term) list) t
  val push_substitution : (variable * term) -> unit t
  
  (* Backtracking *)
  val backtrack_goals : unit -> term list t
  
  (* Monad functions *)
  val return : 'a -> 'a t

  val (let*) : 'a t -> ('a -> 'b t) -> 'b t
  val (let+) : 'a t -> ('a -> 'b) -> 'b t

  val run : unit -> 'a t -> 'a
end = struct
  module IntMap = Map.Make(Int)

    type goal = 
    | Variable of variable
    | Symbol of symbol * goal list

    type state = {
      program       : clause list;
      substitutions : (variable * term) list; 
      clauses       : clause list;
      goals         : goal list;
    }

    type 'a t = state IntMap.t -> 'a * state IntMap.t

    let rec goals_of_terms terms =
      match terms with 
      | [] -> []
      | t :: ts ->
        match view t with
        | Var (n,x) -> 
          (Variable n) :: goals_of_terms ts
        | Sym (h, b) -> 
          (Symbol(h, goals_of_terms b)) :: goals_of_terms ts
    
    let rec terms_of_goals goals =
      match goals with 
      | [] -> []
      | g :: gs ->
        match g with
        | Variable n -> 
          (Var (n, ref None)) :: terms_of_goals gs
        | Symbol (h, b) -> 
          Sym(h, terms_of_goals b) :: terms_of_goals gs

    let make_state p s c g =
      let new_state = {
        program       = p;
        substitutions = s;
        clauses       = c;
        goals         = g;
      } in
      new_state

(*        Stack operations      *)

    let is_empty () map =
      let empty = IntMap.is_empty map in 
      (empty, map)

    let get () map = 
      let key = (IntMap.cardinal map) - 1 in
      let v = IntMap.find key map in
      (v, map)
    
    let pop () map = 
      let key = (IntMap.cardinal map) - 1 in
      let (v, _) = get () map in
      let new_map = IntMap.remove key map in
      (v, new_map)
    
    let rec print_stack map_acc map =
      let empty = IntMap.is_empty map_acc in
      if (empty)
        then 
          ((), map)
        else
          let (s,map_acc) = pop () map_acc in
          print_endline "Klauzule:";
          print_clauses (s.clauses);
          print_endline "";
          print_endline "Termy";
          print_terms (terms_of_goals s.goals);
          print_endline "";
          print_endline "";
          print_endline "";
          print_stack map_acc map

    let set v map = 
      let id = IntMap.cardinal map in
      let new_map = IntMap.add id v map in
      ((), new_map)
      
    let update new_state map =
      let (_, new_map) = pop () map in
      let (_, new_map2) = set new_state new_map in 
      ((), new_map2)


(*        Clearing/Initialising      *)
    let clear_state () _ =
      ((), (IntMap.singleton 0 (make_state [] [] [] [])))
    
    let init_state program _ =
      ((), (IntMap.singleton 0 (make_state program [] program [])))


  (*        State getters/setters       *)
    let get_program () map = 
      let (state, _) = get () map in
      (state.program, map)

    let get_goals () map =
      let state, map = get () map in
      ((terms_of_goals state.goals), map)
    
    let get_clauses () map =
      let (state, map) = get () map in
      (state.clauses, map)

    let get_substitutions () map =
      let (state, _) = get () map in
      (state.substitutions, map)


    let set_goals gs map =
      let new_state = make_state (fst (get_program () map))
                                 (fst (get_substitutions () map))
                                 (fst (get_clauses () map))
                                 (goals_of_terms gs)
      in
      update new_state map
    
    
      
    let set_clauses cs map =
      let new_state = make_state (fst (get_program () map))
                                 (fst (get_substitutions () map))
                                 cs
                                 (goals_of_terms (fst (get_goals () map)))
      in
      update new_state map

    let reset_clauses () map =
      let new_state = make_state (fst(get_program () map))
                                 (fst(get_substitutions () map))
                                 (fst(get_program () map))
                                 (goals_of_terms (fst(get_goals () map)))
      in
      update new_state map
      


    let push_substitution pair map =
      let new_substitutions = pair :: (fst (get_substitutions () map)) 
      in
      let new_state = make_state (fst (get_program () map))
                                 new_substitutions
                                 (fst (get_clauses () map))
                                 (goals_of_terms (fst (get_goals () map)))
      in
      update new_state map


(*        Backtracking      *)
    let backtrack_goals () map =
     (* let _ = print_endline "przed backtrackingiem:" in
      let _ = print_stack map map in 
      let _ = print_endline "po backtrackingu:" in*)
      let (_, new_map) = pop () map in
      (*let _ = print_stack new_map new_map in*) 
      let (empty, new_map) = is_empty () new_map in
      if (empty)
        then 
          ([], new_map)
        else
          let (prev_goals, _) = get_goals () new_map in
          (prev_goals, new_map)
      

(*      Monads operators      *)
    let return x map = (x, map)
    
    let (let*) m f map =
        let (a, map) = m map in
        f a map  

    let (let+) m f map =
      let (a, map) = m map in
      let b = f a in
      (b, map)
    
    let run () computation =
      let res, _ = computation IntMap.empty in
      res

  end
