open Parser;;
open Ast;;
open Interpreter;;
open Stack.BacktrackRefMonad;;
open Helper;;

let rec user_input prompt action =
      match LNoise.linenoise prompt with
      | None -> ()
      | Some input -> 
        action input; 
        user_input prompt action

let history_filename = ".prolog_history"

let rec print_results solutions = 
      match solutions with
      | [] -> print_endline "";
            return ()
      | (name, t) :: ts ->
            print_string name;
            print_string " = ";
            print_terms [t];
            print_endline "";
            print_results ts

type clauses = clause list ref
let program : clauses = ref []


let initialize cs =
      let* _ = init_state cs in
      let* v = get () in
      let x = set v in
      x

  
  
let evaluate ts =
      let* () = solve ts in
      let solution = get_substitutions () in
      solution
  

let main_loop () = 
      user_input "prolog > " (fun input ->
            LNoise.history_add input |> ignore;
            LNoise.history_save ~filename:history_filename |> ignore;
            match input with
            | "." -> print_endline ".";
            | ";" -> print_endline ";";
            | _   ->
                  let query = parse_query_string input in
                  match query with
                  | Query ts   -> 
                        run () (
                              let* _ = initialize (!program) in
                              let* res = evaluate ts in
                              let* _ = print_results res in
                              let* ts2 = backtrack_goals () in
                              let* res2 = evaluate ts2 in
                              print_results res2;
                              )
                  | Filepath f -> 
                        program := parse_file f;
                        print_clauses !program;
      )

let _ = 
      LNoise.history_load ~filename:history_filename |> ignore;
      LNoise.history_set  ~max_length:100 |> ignore;
      ["\n\x1b[38;5;87m" ^ "Welcome to Prolog!" ^ "\x1b[0m\n"; 
      "Type \"[<filepath>].\" to load a program";
      "or type a query starting with \"?-\"";
      "or press ctrl+d to exit.\n"] 
      |> List.iter print_endline;
      main_loop()
  