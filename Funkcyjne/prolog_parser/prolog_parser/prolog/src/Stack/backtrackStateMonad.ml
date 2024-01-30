(*    NAWRACANIE I MUTOWALNY STAN    *)  
open BacktrackStateMonadSig
open State


module BacktrackStateMonad : BacktrackStateMonadSig = struct
  include State
  include Stack

  type 'a t = State.state Stack.IntMap.t -> 'a * State.state Stack.IntMap.t

(*        Backtracking      *)
  let backtrack_goals () map =
    let (_, map)    = Stack.pop () map in
    let (empty, _)  = Stack.is_empty () map in
    if (empty)
      then ([], map)
      else
        let prev_goals = State._get_goals map in
        let _ = State.restore_substitutions () map in
        (prev_goals, map)
    

  let initialize program variables map =
    let new_state = State._init_state program variables in
    Stack._initialize_stack new_state

  
  let rec _print_stack map_acc map =
    let empty = Stack.IntMap.is_empty map_acc in
    if (empty)
      then 
        ((), map)
      else
        let (s,map_acc) = Stack.pop () map_acc in
        State._print_state s;
        _print_stack map_acc map

    
  (*      Monads operators      *)
    let return x map = (x, map)
    
    let (let*) m f map = m map |> fun (a, map) -> f a map

    let (let+) m f map = m map |> fun (a, map) -> (f a, map)
    
    let run () computation =
      let res, _ = computation Stack.IntMap.empty in
      res

end
