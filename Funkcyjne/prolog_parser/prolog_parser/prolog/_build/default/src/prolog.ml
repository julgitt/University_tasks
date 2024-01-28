open Parser;;
open Ast;;
open Interpreter;;
open Stack.BacktrackRefMonad;;
open Printer;;

let rec user_input prompt action =
  match LNoise.linenoise prompt with
  | None -> ()
  | Some input -> 
    action input; 
    user_input prompt action
          
let init_console () =
  LNoise.history_load ~filename:".prolog_history" |> ignore;
  LNoise.history_set  ~max_length:100 |> ignore;
  ["\n\x1b[38;5;199m" ^ "Welcome to Prolog!" ^ "\x1b[0m\n"; 
  "Type \"<filepath>\" to load a program";
  "or type a query";
  "or press ctrl+d to exit.\n"] 
  |> List.iter print_endline; 
  ()

let add_input_to_history input =
  LNoise.history_add input |> ignore;
  LNoise.history_save ~filename:".prolog_history"|> ignore;
  ()
  
type clauses = clause list ref
let program : clauses = ref []
let origin_variables : (variable list ref) = ref []

let rec add_origin_variables terms = 
  match terms with
  | [] -> ()
  | Var(name, _) :: ts -> 
    origin_variables := name :: !origin_variables;
    add_origin_variables ts
  | Sym(name, ts) :: ts2 -> 
    add_origin_variables ts;
    add_origin_variables ts2

let initialize cs =
  let* _ = init_state cs in
  let* v = get () in
  let x = set v in
  x
  
let evaluate ts =
  let* is_solved = solve ts in
  let* solution = get_substitutions () in
  return (is_solved, solution)
  
let get_origin_vars solutions  =
  let is_origin_var name = List.exists (fun s -> s = name) !origin_variables in
  return (List.filter (fun (name, _) -> is_origin_var name) solutions)

let main_loop () =     
  user_input "?- " (fun input ->
    try
      add_input_to_history input;
      let query = parse_query_string input in
      match query with
      | Filepath f -> 
        program := parse_file f;
        print_clauses !program;
        print_endline "";
      | Query ts -> 
        origin_variables := [];
        add_origin_variables ts;
        run () (
          let* _ = initialize (!program) in
          let* (is_solved, solutions) = evaluate ts in
          let* solutions = get_origin_vars solutions in
          print_endline "";
          (match solutions with
          | [] -> 
            if is_solved 
              then  (
                print_endline "\x1b[38;5;40mtrue\x1b[0m.\n";
                return ()
              ) else (
                print_endline "\x1b[38;5;196mfalse\x1b[0m.\n";
                return ()
              );
          | _ ->  
            let* _ = return (print_results solutions) in
            let rec loop () = 
            let* input2 = return (read_line ()) in
            (match input2 with
            | ";" ->  
              let* ts2 = backtrack_goals () in
              let* (_, res2) = evaluate ts2 in
              let* res2 = get_origin_vars res2 in
              (match res2 with
              | []  -> 
                print_endline "\n\x1b[38;5;196mfalse\x1b[0m.\n";
                return ()
              | _   ->  
                let* _ = return (print_results res2) in
                loop ()
            )
          | "." ->  
            print_endline "";
            return ()
          | _ -> return ()
          )
          in loop ()
        ) 
      )
  with  error -> print_error error
)

let _ = 
  init_console ();
  main_loop()
  