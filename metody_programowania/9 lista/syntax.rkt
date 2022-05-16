#lang plait

;   +
;  /  \
; 2     *
;      /   \
;     3      -
;           / \
;          7   21
; 2 + 3 * (7 - 21)

(define-type Op
  (op-add) (op-sub) (op-mul) (op-div) (op-pow) (op-fac) (op-prz)) ;Operatory

(define-type Exp
  (exp-number [n : Number])
  (exp-op-bin [op : Op] [e1 : Exp] [e2 : Exp])
  (exp-op-una [op : Op] [e1 : Exp]))

(define (s-exp->op-bin se)                ;podział bin
  (if (s-exp-symbol? se)
      (let ([sym (s-exp->symbol se)])
        (cond
          [(symbol=? sym '+) (op-add)]
          [(symbol=? sym '-) (op-sub)]
          [(symbol=? sym '*) (op-mul)]
          [(symbol=? sym '/) (op-div)]
          [(symbol=? sym '^) (op-pow)]))
      (error 's-exp->op-bin "Syntax error")))

(define (s-exp->op-una se) ;podział un
  (if (s-exp-symbol? se)
      (let ([sym (s-exp->symbol se)])
        (cond
          [(symbol=? sym '!) (op-fac)]
          [(symbol=? sym '~) (op-prz)]))
      (error 's-exp->op-un "Syntax error")))

(define (s-exp->exp se)                          ;aktualizacja
  (cond
    [(s-exp-number? se) (exp-number (s-exp->number se))]
    [(s-exp-match? `(SYMBOL ANY ANY) se)
     (let ([se-list (s-exp->list se)])
        (exp-op-bin (s-exp->op-bin (first se-list))
                    (s-exp->exp (second se-list))
                    (s-exp->exp (third se-list))))]
        [(s-exp-match? `(SYMBOL ANY) se)
         (let ([se-list (s-exp->list se)])
           (exp-op-una (s-exp->op-una (first se-list))
                       (s-exp->exp (second se-list))))]
    [else (error 's-exp->exp "Syntax error")]))