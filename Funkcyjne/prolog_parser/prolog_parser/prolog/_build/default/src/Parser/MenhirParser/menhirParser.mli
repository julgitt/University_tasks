
(* The type of tokens. *)

type token = 
  | VAR of (string)
  | SYM of (string)
  | RULE
  | PARENTH_OPN
  | PARENTH_CLS
  | FILEPATH of (string)
  | EOF
  | DOT
  | COMMA
  | BR_OPN
  | BR_CLS

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val query: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.query)

val program: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.program)

module MenhirInterpreter : sig
  
  (* The incremental API. *)
  
  include MenhirLib.IncrementalEngine.INCREMENTAL_ENGINE
    with type token = token
  
end

(* The entry point(s) to the incremental API. *)

module Incremental : sig
  
  val query: Lexing.position -> (Ast.query) MenhirInterpreter.checkpoint
  
  val program: Lexing.position -> (Ast.program) MenhirInterpreter.checkpoint
  
end
