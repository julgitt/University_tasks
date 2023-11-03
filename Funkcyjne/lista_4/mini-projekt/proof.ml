open Logic

type goal = (string * formula) list * formula;;

type partial_proof =
| Goal      of goal
| Compl     of theorem
| BottomE   of partial_proof * goal
| ImpI      of partial_proof * goal
| ImpE      of partial_proof * partial_proof * goal

type context =
| Root
| BottomE_ctx       of goal * context
| ImpI_ctx          of goal * context
| ImpE_left_ctx     of goal * partial_proof * context
| ImpE_right_ctx    of partial_proof * goal * context

type proof =
  | Completed     of theorem
  | Incompleted   of goal * context

let proof g f =
  Incompleted(Goal(g, f), Root)

let qed pf =
  match pf with
  | Completed(t)     -> t
  | _(*incompleted*) -> failwith "Proof is not completed"

let goal pf =
  match pf with
  | Incompleted(g,_) -> g
  | _ (*completed*)  -> None;;


let go_up (pf,ctx) =
  match pf with
  | Goal(g)                      -> Some(Incompleted(g,ctx))
  | Compl(t)                     -> None
  | BottomE(part_pf,g)           -> go_up part_pf, BottomE_ctx(g, ctx)
  | ImpI(part_pf,g)              -> go_up part_pf, ImpI_ctx(g, ctx)
  | ImpE(part_pf1, part_pf2, g)  -> 
    let left = go_up part_pf1, ImpE_left_ctx(g,ctx)
    and right = go_up (part_pf2, ImpE_right_ctx(g,ctx))
    in 
    if (left = None) 
      then right
      else left  

let go_down (pf,ctx) =
  match ctx with
  | Root                                -> None
  | BottomE_ctx(g, parent_ctx)          -> go_down BottomE(pf,g), parent_ctx
  | ImpI_ctx(g, parent_ctx)             -> go_down ImpI(pf,g), parent_ctx  
  | ImpE_left_ctx(g, pf_r, parent_ctx)  -> 
      let up = go_up (pf_r, ImpE_right_ctx(g, pf, parent_ctx))
      and down = go_down (ImpE(pf, pf_r, g), parent_ctx)
      in
      if up = None
        then Some down
        else Some up 
  | ImpE_right_ctx(pf_l, g, parent_ctx) -> 
      let up = go_up (pf_l, ImpE_left_ctx(g, pf, parent_ctx))
      and down = go_down (ImpE(pf, pf_l, g), parent_ctx)
      in
      if up = None
        then Some down
        else Some up 
 
let next pf =
  match pf with
  | Completed(_)        -> failwith "Proof is completed"
  | Incompleted(g, ctx) ->
    match go_down (Goal g), ctx with
    | None    -> failwith "Failed to find new goal"
    | Some(g) -> g

let intro name pf =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let apply f pf =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let apply_thm thm pf =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let apply_assm name pf =
  (* TODO: zaimplementuj *)
  failwith "not implemented"

let pp_print_proof fmtr pf =
  match goal pf with
  | None -> Format.pp_print_string fmtr "No more subgoals"
  | Some(g, f) ->
    Format.pp_open_vbox fmtr (-100);
    g |> List.iter (fun (name, f) ->
      Format.pp_print_cut fmtr ();
      Format.pp_open_hbox fmtr ();
      Format.pp_print_string fmtr name;
      Format.pp_print_string fmtr ":";
      Format.pp_print_space fmtr ();
      pp_print_formula fmtr f;
      Format.pp_close_box fmtr ());
    Format.pp_print_cut fmtr ();
    Format.pp_print_string fmtr (String.make 40 '=');
    Format.pp_print_cut fmtr ();
    pp_print_formula fmtr f;
    Format.pp_close_box fmtr ()
