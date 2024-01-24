type reason =
| EofInComment
| InvalidNumber   of string
| InvalidChar     of char
| UnexpectedToken of string

exception Parse_error      of reason

exception Not_unifiable
exception Predicate_base_is_empty

exception Cannot_open_file of
  { fname   : string
  ; message : string
  }
