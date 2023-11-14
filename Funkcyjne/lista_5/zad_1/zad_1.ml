(*
   Zadanie 1 (3p). Interesującą techniką w programowaniu funkcyjnym jest oddzielenie rekursji od reszty
definicji. Dla funkcji rekurencyjnych możemy to osiągnąć definiując kombinator punktu stałego
let rec fix f x = f (fix f) x
a pozostałe funkcje rekurencyjne definiować przy jego pomocy. Na przykład naiwna definicja funkcji obliczającej
liczby Fibonacci’ego może wyglądać następująco.
let fib_f fib n =
if n <= 1 then n
else fib (n-1) + fib (n-2)
let fib = fix fib_f
Zaletą tego podejścia jest to, że łatwo teraz zmienić kod tak, by każde wywołanie funkcji rekurencyjnej
wykonywało dodatkową pracę — wystarczy użyć innego kombinatora punktu stałego. Zdefiniuj następujące
wersje kombinatora punktu stałego:
• fix_with_limit : int -> ((’a -> ’b) -> ’a -> ’b) -> ’a -> ’b
— działa jak zwykły fix, ale dostaje dodatkowy parametr oznaczający maksymalną głębokość rekursji.
W przypadku przekroczenia limitu funkcja powinna zgłosić wyjątek.
• fix_memo : ((’a -> ’b) -> ’a -> ’b) -> ’a -> ’b — kombinator, który dodatkowo implementuje spamiętywanie, tzn. zapamiętuje wyniki wszystkich dotychczasowych wywołań. Gdy dana
funkcja była kiedyś wołana z danym parametrem, to nie powinniśmy jej liczyć po raz kolejny, tylko od
razu zwrócić zapamiętaną wartość. Np. gdy zdefiniujemy fib jako
let fib = fix_memo fib_f
to dla danego n pierwsze wywołanie fin n powinno policzyć się w czasie liniowym względem n,
a każde następne w czasie stałym. Zapoznaj się z modułem Hashtbl z biblioteki standardowej w celu
efektywnej implementacji funkcji fix_memo.
*)
let rec fix f x = f (fix f) x

let fib_f fib n =
  if n <= 1 
    then n
    else fib (n-1) + fib (n-2)
  let fib = fix fib_f

(*: int -> ((’a -> ’b) -> ’a -> ’b) -> ’a -> ’b*)
let rec fix_with_limit num f x =
  if num = 0 then failwith "RecursionError: maximum recursion depth exceeded"
  else f (fix_with_limit (num - 1) f) x
 
(* ((’a -> ’b) -> ’a -> ’b) -> ’a -> ’b *)  
let fix_memo f =
  let memo = Hashtbl.create 100
  in
  let rec fix_m x =
    match Hashtbl.find memo x with
    | Some value -> value
    | None ->
      let result = f (fix_m) x
      in
      Hashtbl.add memo x result
      result
  in fix_m
