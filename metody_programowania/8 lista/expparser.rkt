#lang racket
(require "syntax.rkt")
(require "parsing.rkt")
(require (only-in plait s-exp-content))
; ====================================================
; Gramatyki bezkontekstowe

; * Terminale (tokeny)
; * Nieterminale (np. "expression", "operator")
; * Lista produkcji:
;   "expression" -> NUMBER
;   "expression" -> "expression" "operator" "expression"

; 2 + 2 + 2

; "expression" -> "expression" "add-operator" "mult-exp"
; "expression" -> "mult-exp"
; "mult-exp"   -> "mult-exp" "mult-operator" "atom-exp"
; "mult-exp"   -> "atom-exp"
; "atom-exp"   -> NUMBER
; "atom-exp"   -> ( "expression" )

; ====================================================
(define(find op)
  (cond [(equal? op (op-add)) +]
        [(equal? op (op-sub)) -]
        [(equal? op (op-mul)) *]
        [(equal? op (op-div)) /]))

(define grammar
  `(("operator"
     ((+) ,op-add)
     ((-) ,op-sub)
     ((*) ,op-mul)
     ((/) ,op-div))
    
    ("expression"
     (("simple-expr" "operator" "simple-expr")
          ,(lambda (e1 op e2) ((find op) e1 e2))) ;(exp-op find op)
     (("simple-expr") ,(lambda (e) e)))
    
    ("simple-expr"
     ((NUMBER)           ,identity)
     (( ("expression") ) ,(lambda (e) e)))))

(define (run-exp-parser se)
  (run-named-parser grammar "expression" (list se)))

(define (parse-exp se)
  (run-exp-parser (s-exp-content se)))