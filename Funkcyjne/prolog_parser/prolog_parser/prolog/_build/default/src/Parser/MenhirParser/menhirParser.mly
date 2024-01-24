%token<string> VAR SYM
%token <string> FILEPATH
%token BR_OPN BR_CLS PARENTH_OPN PARENTH_CLS
%token COMMA DOT RULE
%token EOF

%type<Ast.program> program
%start program

%type<Ast.query> query
%start query

%{

open Ast

(*let current_pos () =
  let start_p = symbol_start_pos () in
  let end_p   = symbol_end_pos () in
  { start  = start_p
  ; length = end_p.pos_cnum - start_p.pos_cnum
  }

let make data =
  { pos  = current_pos ()
  ; data = data
  }*)

%}

%%

symbol
: SYM { $1 }
;

/* ========================================================================= */

term
: PARENTH_OPN term PARENTH_CLS { ($2) }
| VAR                { Var ($1, ref None) }
| symbol             { Sym ($1, []) }
| symbol PARENTH_OPN term_list PARENTH_CLS { Sym($1, $3) }
;

/* ========================================================================= */

term_list
: term                 { [ $1 ]   }
| term COMMA term_list { $1 :: $3 }
;

/* ========================================================================= */

clause
: term DOT                       { Fact $1      }
| term RULE term_list DOT { Rule($1, $3) }
;

clause_list_rev
: /* empty */            { []       }
| clause_list_rev clause { $2 :: $1 }
;

clause_list
: clause_list_rev { List.rev $1 }
;

/* ========================================================================= */

program
: clause_list EOF { $1 }
;

query
: term_list DOT {Query $1 }
| BR_OPN FILEPATH BR_CLS {Filepath $2}
;
