#lang racket

;minimum
(define (minimum xs)
    (define (find-min xs min)
    (cond
      [(null? xs)
       min]
      [(< (car xs) min)
       (find-min (cdr xs) (car xs))]
      [else
       (find-min (cdr xs) min)]))
  (find-min xs +inf.0))

;delete element
(define (delete x xs)
  (cond
    [(null? xs) null]
    [(equal? (car xs) x) (cdr xs)]
    [else
     (cons (car xs) (delete x (cdr xs)))]))

(define (select xs)
  (cons (minimum xs) (delete (minimum xs) xs)))
  
 ;select sort
(define (select-sort xs)
  (cond
    [(null? xs) null]
    [else
     (cons (car (select xs))(select-sort (cdr (select xs))))]))