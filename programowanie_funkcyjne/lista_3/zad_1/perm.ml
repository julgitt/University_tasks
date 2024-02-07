module type OrderedType = sig
  type t
  val compare : t -> t -> int
end


module type S = sig
  type key
  type t

  (** permutacja jako funkcja *)
  val apply : t -> key -> key
  (** permutacja identycznościowa *)
  val id : t
  (** permutacja odwrotna *)
  val invert : t -> t
  (** permutacja która tylko zamienia dwa elementy miejscami *)
  val swap : key -> key -> t
  (** złożenie permutacji (jako złożenie funkcji) *)
  val compose : t -> t -> t
  (** porównywanie permutacji *)
  val compare : t -> t -> int
end

module Make(Key : OrderedType) = struct
  
  module Function = Map.Make(Key)

  type key = Key.t
  type t = key Function.t * key Function.t


  let apply t key =
    let first = fst t
    in match Function.find_opt key first with
    | Some value        -> value
    | None (*identity*) -> key;;

  let id = (Function.empty, Function.empty);;

  let invert t =
    let first = fst t
    and second = snd t
    in (second, first);;
  
  let swap key1 key2 =
    if key1 == key2
    then id
    else 
      let f = Function.add key1 key2 
              (Function.add key2 key1 
              Function.empty)
    in (f, f);;

  let compose t1 t2 =
    let first = Function.merge (fun _ val1 val2 ->
                          match val1, val2 with
                          (* a ->  b, b -> c  =  a -> c*)
                          | Some x, _ -> Some (apply t2 x) 
                          (* a -> b, b -> b = a -> b*)
                          | _, Some x -> Some x
                          (* a -> a, a -> a = a -> a *)
                          | _ -> None
                          ) (fst t1) (fst t2)

    and second = Function.merge (fun _ val1 val2 ->
                          match val1, val2 with
                          | Some x, _ -> Some (apply t1 x) 
                          | _, Some x -> Some x
                          | _ -> None
                          ) (snd t2) (snd t1)
    in (first, second);;
  
  let compare t1 t2 =  if (Function.compare Key.compare (fst t1) (fst t2)) == 0 
  		       then 1 
  		       else 0;;

end
