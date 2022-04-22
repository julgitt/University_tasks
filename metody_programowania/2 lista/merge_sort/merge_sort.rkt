#lang racket


(define (split xs)
  (define (it n xs ys)
    (cond
      [(= n 0)
       (cons (reverse ys) xs)]
      [else (it (- n 1) (cdr xs) (cons (car xs) ys))]
      ))
  (it (quotient (length xs) 2) xs null))


(define (merge xs ys)
  (define (result zs xs ys)
    (cond
      [(and (null? xs) (null? ys)) zs]
      [(null? xs) (append (reverse zs) ys)]
      [(null? ys) (append (reverse zs) xs)]
      [(> (car xs)(car ys))
       (result (cons (car ys) zs)
               xs (cdr ys))]
      [else
       (result (cons (car xs) zs)
              (cdr xs) ys)]))
  (result (list) xs ys))


  (define (merge-sort xs)
    (if (<= (length xs) 1)
        xs
        (merge (merge-sort (car(split xs))) (merge-sort (cdr(split xs))))))
  