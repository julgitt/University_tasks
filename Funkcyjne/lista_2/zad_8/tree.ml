type 'a tree =
  | Leaf
  | Node of 'a t * 'a * int * 'a t

and 'a t = 'a tree

let tree t = t

let empty = Leaf

let create tree1 elem tree2  =
  match tree1, tree2 with
  | Leaf, Leaf -> Node(Leaf, elem, 1, Leaf)
  | Leaf, (Node _ as tree) | (Node _ as tree), Leaf   -> Node(tree, elem, 1, Leaf)
  | Node(_,_,len1,_), Node(_,_,len2,_) -> 
      if len2 < len1
      then Node(tree1, elem, len2 + 1, tree2)
      else Node(tree2, elem, len1 + 1, tree1);;
      
let rec merge tree1 tree2 =
  match tree1, tree2 with
  | Leaf, Leaf -> Leaf
  | Leaf, (Node _ as tree) | (Node _ as tree), Leaf -> tree
  | Node(left1,val1,_,right1),
    Node(left2,val2,_,right2) -> 
      if val1 < val2
      then create left1 val1 (merge tree2 right1)
      else create left2 val2 (merge tree1 right2);;

      
let add tree elem = 
  merge tree (create Leaf elem Leaf);;

let delete tree =
  match tree with
  | Leaf                    -> Leaf 
  | Node(left, _, _, right) -> merge left right  
