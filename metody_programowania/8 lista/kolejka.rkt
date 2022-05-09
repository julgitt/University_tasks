zaraz wysle#lang racket
(provide
 mqueue?
 nonempty-mqueue/c
 (contract-out
  [mqueue-empty? (-> mqueue? boolean?)]
  [mqueue-make   (-> mqueue?)]
  [mqueue-push   (-> mqueue? any/c any/c)]
  [mqueue-pop    (-> nonempty-mqueue/c any/c)]
  [mqueue-peek   (-> nonempty-mqueue/c any/c)]
  [mqueue-join   (-> nonempty-mqueue/c nonempty-mqueue/c any/c)]))

(define (insert-after p1 p2)
  (define p3 (mcdr p1))
  (set-mcdr! p2 p3)
  (set-mcdr! p1 p2))

(struct mqueue
  ([front #:mutable] [back #:mutable]))

(define (mqueue-empty? q)
  (null? (mqueue-front q)))

(define nonempty-mqueue/c
  (and/c mqueue? (not/c mqueue-empty?)))

(define (mqueue-make)
  (mqueue null null))

(define (mqueue-push q x)
  (define p (mcons x null))
  (if (mqueue-empty? q)
      (set-mqueue-front! q p)
      (set-mcdr! (mqueue-back q) p))
  (set-mqueue-back! q p))

(define/contract (mqueue-pop q)
  (-> nonempty-mqueue/c any/c)
  (define p (mqueue-front q))
  (set-mqueue-front! q (mcdr p))
  (mcar p))

(define (mqueue-peek q)
  (mcar (mqueue-front q)))

(define (mqueue-join q1 q2)
  (set-mcdr! (mqueue-back q1) (mqueue-front q2))
  (set-mqueue-back! q1 (mqueue-back q2))
  (set-mqueue-front! q2 null))

(define/contract (mreverse! q)
  (-> nonempty-mqueue/c any/c)
  (define pointer-back (mqueue-back q))
  (set-mqueue-back! q (mqueue-front q))
  (set-mqueue-front! q pointer-back)
  (define (it q prev next)
    (cond [(null? next)
           (set-mcdr! q prev)]
          [else(set-mcdr! q prev)
               (it next q (mcdr next))]))
  (it (mqueue-back q) null (mcdr(mqueue-back q)))) ;6 5 4

(define (mrev! xs)
  (define (it q prev next)
    (cond [(null? next)
           (set-mcdr! q prev) q]
          [else(set-mcdr! q prev)
               (it next q (mcdr next))]))
  (it xs null (mcdr xs))) 




