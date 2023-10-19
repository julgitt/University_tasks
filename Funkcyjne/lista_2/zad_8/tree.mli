type 'a t

type 'a tree =
  | Leaf
  | Node of 'a t * 'a * int * 'a t

val empty : 'a t

val add : 'a t -> 'a -> 'a t

val delete : 'a t -> 'a t

val tree : 'a t -> 'a tree
