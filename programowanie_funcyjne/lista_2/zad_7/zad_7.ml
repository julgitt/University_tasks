(*Zadanie 7 (4p). Kopiec lewicowy, to drzewo binarne (etykietowane w węzłach), które ma następujące dwie własności:
- zachowany jest porządek kopcowy, tzn. dla każdego węzła przechowywana wartość jest nie większa niż każda wartość w jego dzieciach,
- dla każdego węzła, długość prawego kręgosłupa lewego syna jest nie mniejsza niż długość prawego kręgosłupa prawego syna (długość prawego kręgosłupa, to odległość od wierzchołka do liścia idąc cały czas w prawo).

Zaproponuj reprezentację drzew lewicowych tak, aby dla każdego wierzchołka dało się policzyć długość prawego kręgosłupa w czasie stałym. 
Następnie zaimplementuj następujące operacje.
- Tworzenie węzła drzewa lewicowego z dwóch drzew i podanej etykiety (tzw. smart-constructor). Możesz założyć, że podana etykieta jest nie większa niż wszystkie etykiety w podanych drzewach.
- Złączanie dwóch drzew lewicowych w jedno. W tym celu należy wybrać drzewo o najmniejszym korzeniu, rozbić je na etykietę (nowy korzeń) i dwa poddrzewa, z których prawe należy złączyć z nie wybranym drzewem.
- Wstawianie elementu do drzewa lewicowego. Najłatwiej to zrobić przy pomocy już zaimplementowanego złączania.
- Usuwanie najmniejszego elementu z drzewa. Powstałe poddrzewa należy złączyć w jedno.
Do porównywania elementów użyj wbudowanej funkcji porównującej (<).*)

type 'a tree =
  | Leaf
  | Node of 'a tree * 'a * int * 'a tree

let empty = Leaf
  
  
let create tree1 elem tree2  =
  match tree1, tree2 with
  | Leaf, Leaf -> Node(Leaf, elem, 1, Leaf)
  | Leaf, (Node _ as tree) | (Node _ as tree), Leaf   -> Node(tree, elem, 1, Leaf)
  | Node(_,_,len1,_), Node(_,_,len2,_) -> 
      if len2 < len1
      then Node(tree1, elem, len2 + 1, tree2)
      else Node(tree2, elem, len1 + 1, tree1);;

let t1 = create (Node(Leaf, 1, 1, Leaf)) 3 (Node(Leaf, 2, 1, Leaf));;
let t2 = create (Node(Leaf, 1, 1, Leaf)) 2 Leaf;;
(*Złączanie dwóch drzew lewicowych w jedno. 
W tym celu należy wybrać drzewo o najmniejszym korzeniu, rozbić je na etykietę (nowy korzeń) i dwa poddrzewa,
z których prawe należy złączyć z nie wybranym drzewem.*)
  
let rec merge tree1 tree2 =
  match tree1, tree2 with
  | Leaf, Leaf -> Leaf
  | Leaf, (Node _ as tree) | (Node _ as tree), Leaf -> tree
  | Node(left1,val1,_,right1),
    Node(left2,val2,_,right2) -> 
      if val1 < val2
      then create left1 val1 (merge tree2 right1)
      else create left2 val2 (merge tree1 right2);;

merge (Node (Leaf, 3, 1, Leaf)) t2;;

let add tree elem = 
  merge tree (create Leaf elem Leaf);;

let delete tree =
  match tree with
  | Leaf                    -> Leaf 
  | Node(left, _, _, right) -> merge left right  
