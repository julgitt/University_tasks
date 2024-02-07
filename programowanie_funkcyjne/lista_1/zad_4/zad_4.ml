(*Dla strumieni z poprzedniego zadania zdefiniuj funkcję scan, 
która dla zadanej funkcji f: ’a -> ’b -> ’a, wartości początkowej a: ’a i strumienia s elementów typu ’b tworzy nowy strumień,
którego każdy element jest wynikiem „zwinięcia” początkowego segmentu strumienia s aż do bieżącego elementu włącznie za pomocą funkcji f,
tj. w strumieniu wynikowym element o indeksie n ma wartość (f (. . . (f (f a (s 0)) (s 1)) . . .) (s n)),
Wskazówka: liczby naturalne mają strukturę. 
Od czego zaczyna się nowy strumień? 
Jak mając n-ty element nowego strumienia policzyć następny?*)

let stream x = x

let g x y = x + y

(*('a -> int -> 'a) -> 'a -> int -> 'a = <fun>*)
let rec scan f a s =
        fun n -> 
            if n = 0 then f a (s 0)
            else f (scan f a s (n - 1)) (s n)
            
scan g 0 stream (* dla x - suma elementów od 0 do x *)

(* to inny przykład : (scan f 10 stream) 5
f ((scan f 10 stream) (4) (stream 5))
f ((f ((scan f 10 stream) (3) (stream 4))) 6)
f ((f (( f (( scan f 10 stream (2) (stream 3))) 5))) 6)
...
f ... (f (f 10  1) 2) ... 6 = 10*)

