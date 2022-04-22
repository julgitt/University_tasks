#lang racket
;zad 3
(define/contract (suffixes xs)
  (-> list? list?)
    (cond
      [(null? xs) (list xs)]
      [else
       (cons xs (suffixes (cdr xs)))]))

;zad 4
(define/contract (sublists xs)
  (-> list? (listof list?))
   (if (null? xs)
       (list null)
       (append-map
         (lambda(ys) (cons(cons(car xs) ys) (list ys)))
         (sublists (cdr xs)))))

;(define/contract (sublists xs)
 ; (-> list? (listof list?))
  ;(if (null? xs) (list)
   ;   (append-map (lambda (x y)(map (lambda (z)(cons x z)) (sublists y)))
    ;             (cdr(reverse(suffixes (reverse xs))))(cdr(suffixes xs)))))

;zad 5
;                          n n p  
;(parametric->/c [a b] (-> a b a))
(define/contract (f a b)
  (parametric->/c [a b] (-> a b a))
  a)
;                                n n n      p p  n p
;(parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
(define/contract (g h f a)
  (parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
  (h a (f a)))

;                                n n      p p     n p
;(parametric->/c [a b c] (-> (-> b c) (-> a b)(-> a c)))

(define/contract (h g f)
  (parametric->/c [a b c] (-> (-> b c) (-> a b)(-> a c)))
  (compose g f))
;                                n p  n  p
;(parametric->/c [a] (-> (-> (-> a a) a) a))

(define/contract (p f)
  (parametric->/c [a] (-> (-> (-> a a) a) a))
  f)