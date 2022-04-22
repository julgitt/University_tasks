#lang racket

(define (Fibonacci n)
  (if (= n 0)
      0
      (if (= n 1)
          1
          (+ (Fibonacci (- n 1)) (Fibonacci (- n 2))))))



(define (Fibonacci-iter n)
  (define (it n prev1 prev2)
    (if (= n 0)
        prev2
        (if (= n 1)
            prev1
            (it (- n 1) (+ prev1 prev2) prev1 ))))
  (it n 1 0))


