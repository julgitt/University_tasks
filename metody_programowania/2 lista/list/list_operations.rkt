#lang racket

;zadanie 4
;sprawdzanie czy element znajduje sie na liscie
(define (elem? x xs)
  (cond
    [(null? xs) #f]
    [(equal? (car xs) x) #t]
    [else(elem? x (cdr xs))]))

;zadanie 5 maksimum

(define (maximum xs)
  (define (find-max xs max)
    (cond
      [(null? xs)
       max]
      [(> (car xs) max)
       (find-max (cdr xs) (car xs))]
      [else
       (find-max (cdr xs) max)]))
  (find-max xs -inf.0))

;zadanie 6 zwraca sufiksy listy
(define (suffixes xs)
    (cond
      [(null? xs) (list xs)]
      [else
       (cons xs (suffixes (cdr xs)))]))
 
(define (sorted? xs)
    (cond
      [(null? xs) #t]
      [(null? (cdr xs)) #t]
      [else
       (if (> (car xs) (second xs))
           #f
           (sorted? (cdr xs)))]))
      
 