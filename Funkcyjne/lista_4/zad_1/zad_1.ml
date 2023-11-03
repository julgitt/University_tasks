
    (*
  type 'a nlist =
    | Nil
    | Zero of ('a * 'a) nlist
    | One  of 'a * ('a * 'a) nlist*)
  
  type 'a nlist =
    | Nil
    | One of 'a * ('a * 'a) nlist
    | Two of 'a * ('a * 'a) nlist
  
(*
    let rec cons : 'a. 'a -> 'a nlist -> 'a nlist =
      fun x xs ->
      match xs with
      | Nil        -> One(x, Nil)
      | Zero xs    -> One(x, xs)
      | One(y, xs) -> Zero (cons (x, y) xs)
      *)

  let rec cons : 'a. 'a -> 'a nlist -> 'a nlist =
    fun x xs ->
    match xs with
    | Nil       -> One (x, Nil)
    | One (y, ys) -> Two ((x, y), ys)
    | Two (y, ys) -> One (x, cons (y, ys))
  
(*
  let rec view : 'a. 'a nlist -> ('a * 'a nlist) option =
    function
    | Nil -> None
    | Zero xs ->
      begin match view xs with
      | None -> None
      | Some((x, y), xs) -> Some(x, One(y, xs))
      end
    | One(x, xs) -> Some(x, Zero xs)
  *)
  let rec view : 'a. 'a nlist -> ('a * 'a nlist) option =
    function
    | Nil -> None
    | One (x, xs) -> Some (x, Two (x, xs))
    | Two ((x, y), xs) ->
      begin match view xs with
      | None -> None
      | Some ((z, w), xs') -> Some (z, One (w, xs'))
      end
  (*
    let rec nth : 'a. 'a nlist -> int -> 'a =
      fun xs n ->
      match xs with
      | Nil -> raise Not_found
      | Zero xs ->
        let (x, y) = nth xs (n / 2) in
        if n mod 2 = 0 then x
        else y
      | One(x, xs) ->
        if n = 0 then x
        else nth (Zero xs) (n-1)
  *)
  let rec nth : 'a. 'a nlist -> int -> 'a =
    fun xs n ->
    match xs with
    | Nil -> raise Not_found
    | One (x, xs') -> if n = 0 then x else nth xs' (n - 1)
    | Two ((x, y), xs') ->
      if n mod 2 = 0 then x else y
  
  let rec add_one : 'a. 'a nlist -> 'a nlist =
    fun xs ->
    match xs with
    | Nil -> One (1, Nil)
    | One (x, xs') -> Two (x, add_one xs')
    | Two ((x, y), xs') -> One (0, add_one xs')