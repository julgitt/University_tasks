(*Zdefiniuj funkcję tabulate, której wynikiem powinna być lista elementów strumienia leżących w zadanym zakresie indeksów.
Pusta lista to [], natomiast binarny operator (::) dołącza element z przodu listy (tak jak cons w Rackecie).
Wykorzystaj możliwość definiowania parametrów opcjonalnych dla funkcji — niech początek zakresu indeksów będzie opcjonalny i domyślnie równy 0.*)

(*Przykład: pierwszy argument funkcji f w deklaracji 
let f ?(x=0) y = x + y
ma etykietę x i jest opcjonalny, a jego wartość domyślna wynosi 0. 
Wyrażenie (f 3) jest równoważne wyrażeniu (f ~x:0 3) (i ma wartość 3), zaś wartością wyrażenia (f ~x:42 3) jest 45.*
*)

(*?l:int -> int -> (int -> 'a) -> 'a list*)
let rec tabulate ?(l=0) r s = 
    if l > r then []
    else s l :: tabulate ~l:(l + 1) r s
    
    
tabulate ~l:2 8 stream
tabulate 8 stream
