 
(*Strumień (tj. nieskończony ciąg) elementów typu t możemy reprezentować za pomocą funkcji s: int -> t w taki sposób,
że wartością wyrażenia s 0 jest pierwszy element strumienia, wyrażenia s 1 — drugi itd.
Używając powyższej reprezentacji zdefiniuj następujące funkcje działające na strumieniach (tam, gdzie to możliwe, funkcje te powinny być polimorficzne, tj. powinny działać na strumieniach o elementach dowolnego typu):

• hd, tl — funkcje zwracające odpowiednio głowę i ogon strumienia;*)

let s x = x + 1 (* Przykładowy strumień *)

(*hd : (int -> 'a) -> 'a = <fun>*)
let hd s = s 0

(*tl : (int -> 'a) -> int -> 'a = <fun>*)
let tl s = fun x -> s (x + 1)


(*add — funkcja, która dla zadanego strumienia tworzy nowy strumień, 
którego każdy element jest większy o zadaną stałą od odpowiadającego mu elementu oryginalnego strumienia;*)

(*add : ('a -> int) -> int -> 'a -> int*)
let add s x = fun y -> s y + x


(*map — funkcja, która dla zadanego strumienia tworzy nowy strumień,
którego każdy element jest wynikiem obliczenia zadanej funkcji dla argumentu będącego odpowiadającym mu elementem oryginalnego strumienia 
(tak, jak map dla list skończonych);*)

(*map : ('a -> 'b) -> ('b -> 'c) -> 'a -> 'c = <fun>*)
let map s f = fun x -> f (s x)


(*map2 — jak wyżej, ale dla podanej funkcji dwuargumentowej i dwóch strumieni, 
np. map2 (+) s1 s2 policzy sumę dwóch strumieni po współrzędnych;*)

(*map2 : ('a -> 'b) -> ('a -> 'c) -> ('b -> 'c -> 'd) -> 'a -> 'd*)
let map2 s1 s2 f = fun x -> f (s1 x)(s2 x)
(* jeżeli chcemy mieć różne współrzędne w strumieniach, to do fun x dodajemy jeszcze drugi argument *)


(*replace — funkcja, która dla zadanego indeksu n, wartości a i strumienia s tworzy nowy strumień, 
w którym wszystkie wartości są takie jak w strumieniu s, oprócz n-tego elementu, który ma wartość a;*)


(*'a -> 'b -> ('a -> 'b) -> 'a -> 'b *)
let replace n a s = fun x -> if x = n then a else s x


(*take_every — funkcja, która dla zadanego indeksu n i strumienia s tworzy nowy strumień złożony z co n-tego elementu strumienia s.*)

(*int -> (int -> 'a) -> int -> 'a = <fun>*)
let take_every n s = fun x -> s (n * x)

(*Zdefiniuj przykładowe strumienie i przetestuj swoją implementację.

*Wskazówka: nie szukaj w internecie o strumieniach, bo strumienie zwykle reprezentuje się w zupełnie inny sposób. W tym zadaniu chcemy przećwiczyć funkcje wyższego rzędu, więc strumienie reprezentujemy tak jak reprezentowaliście ciągi na Analizie Matematycznej: jako funkcje z liczb naturalnych w elementy ciągu (strumienia).**)
