#lang racket

(define-syntax my-and
  (syntax-rules ()
    [(my-and) #t]
    [(my-and a1 a2 ...)
     (if a1 (my-and a2 ...) #f)]))

(define-syntax my-or
  (syntax-rules ()
    [(my-or) #f]
    [(my-or a1 a2 ...)
     (if a1  #t (my-or a2 ...))]))

(define-syntax my-let
  (syntax-rules ()
    [(my-let () exp) exp]
    [(my-let ([x1 a1] [x2 a2] ...) exp)
     ((lambda (x1 x2 ...) exp) a1 a2 ...)]))

(define-syntax my-let*
  (syntax-rules ()
    [(my-let* () exp) exp]
    [(my-let* ([x1 a1] [x2 a2] ...) exp)
     (my-let ([x1 a1]) (my-let* ([x2 a2] ...)) exp)]))

(define (a b c)
  (my-let ((d 2) (e 3))
          (+ d e b c))) 