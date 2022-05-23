#lang plait

(module+ test
  (print-only-errors #t))

;; abstract syntax -------------------------------

(define-type Op
  (add)
  (sub)
  (mul)
  (div))

(define-type Exp
  (numE [n : Number])
  (opE [op : Op] [exp : (Listof Exp)]))

;; parse ----------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{SYMBOL ANY ...} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (parse-rest (rest (s-exp->list s))))]
    [else (error 'parse "invalid input")]))

(define (parse-rest [s : (Listof S-Exp)]) : (Listof Exp)
  (cond
    [(empty? s) '()]
    [else
     (cons (parse (first s))
           (parse-rest (rest s)))]))
    

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [else (error 'parse "unknown operator")]))
                 
(module+ test
  (test (parse `2)
        (numE 2))
  (test (parse `{+ 2 1 4})
        (opE (add) (list(numE 2) (numE 1) (numE 4))))
  (test (parse `{*})
        (opE (mul) (list)))
  (test (parse `{+ {* 3 4} 8 7})
        (opE (add)
             (list(opE (mul) (list(numE 3) (numE 4)))
             (numE 8) (numE 7))))
  (test/exn (parse `{{+ 1 2}})
            "invalid input")
  (test/exn (parse `{^ 1 2})
            "unknown operator"))
  
;; eval --------------------------------------

(define-type-alias Value Number)

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(div) /]))

(define (find-neutral [op : Op])
   (type-case Op op
    [(add) 0]
    [(sub) 0]
    [(mul) 1]
    [(div) 1]))


(define (it xs op acc)
    (if (empty? xs)
        acc
        (it (rest xs) op (op acc (eval(first xs))))))

(define (eval [e : Exp]) : Value
  (type-case Exp e
    [(numE n) n]
    [(opE o exp)
     (cond
       [(empty? exp) (find-neutral o)]
       [(equal? (length exp) 1) (eval (first exp))]
       [else 
        (it (rest exp) (op->proc o) (eval (first exp)))])]));zrob normalna iteracje i bedzie git

(define (run [e : S-Exp]) : Value
  (eval (parse e)))

(module+ test
  (test (run `2)
        2)
  (test (run `{+ 2 1})
        3)
  (test (run `{* 2 1})
        2)
  (test (run `{+ {* 2 3} {+ 5 8}})
        19)
   (test (run `{/ {+ 3 3 3} 3 3})
        1)
  (test (run `{+ {* 2 3 6} {+ 5 8 8}})
        57))

;; printer ———————————————————————————————————-

(define (print-value [v : Value]) : Void
  (display v))

(define (main [e : S-Exp]) : Void
  (print-value (eval (parse e))))