#lang racket

(require rackunit)

;tree structure
(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define (tree? x)
  (cond [(leaf? x) #t]
        [(node? x) (and (tree? (node-l x)) (tree? (node-r x)))]
        [else #f]))

(define example-tree (node (node (leaf) 1 (node (leaf) 2 (leaf)))
                           3
                           (node (node (leaf) 4 (leaf))
                                 5
                                 (node (leaf) 6 (leaf)))))
(define (insert-bst x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond [(= x (node-elem t)) t]
               [(< x (node-elem t))
                (node
                 (insert-bst x (node-l t))
                 (node-elem t)
                 (node-r t))]
               [else
                (node
                 (node-l t)
                 (node-elem t)
                 (insert-bst x (node-r t)))])]))

;_________________________________________________________________________________________

;ZAD 2
;fold-tree
(define (fold-tree f acc t)
  (cond [(leaf? t) acc]
        [else (f (fold-tree f acc (node-l t)) (node-elem t) (fold-tree f acc (node-r t)))]))
      
;suma wszystkich wartości występujących w drzewie,
(define (tree-sum t)
  (fold-tree + 0 t))

;odwrócenie kolejności: zamiana lewego i prawego poddrzewa
;wszystkich węzłów w drzewie,
(define (tree-flip t)
  (fold-tree (lambda (l t r) (node r t l)) (leaf) t))

;wysokosć drzewa 
(define (tree-height t)
  (fold-tree (lambda (x t z) (+ 1 (max x z))) 0 t))

; para złożona z wartości najmniejszej i najwiekszej w drzewie bst
(define (tree-span t)
  (cons
   (fold-tree min (node-elem t) t)
   (fold-tree max (node-elem t) t)))

;lista wszystkich elementów występujących w drzewie, w kolejności indeksowej.
(define (flatten t)
   (fold-tree (lambda (l t r) (append l (list t) r)) null t))

;_________________________________________________________________________________________
;ZAD 3

;predykat sprawdzający, czy zadane drzewo spełnia własność BST.
(define (bst? t)
   (cond [(leaf? t) #t]
         [else (and (if (< (find-min (node-r t)) (node-elem t))
                         (bst? (node-l t))
                         #f)
               (if (< (node-elem t) (find-max (node-l t)))
                         (bst? (node-r t))
                         #f))]))

(define (find-max t)
  (if (leaf? t)
      +inf.0
      (if (leaf? (node-l t))
          (node-elem t)
          (find-min (node-l t)))))        
 (define (node-sum t s)
  (node (node-l s) (+ (node-elem t) (node-elem s)) (node-r s)))
               
 (define (node-sum t s)
  (node (node-l s) (+ (node-elem t) (node-elem s)) (node-r s)))

(define (sum-paths t)
  (if (leaf? t) t
         (node
          (if (node? (node-l t))
            (sum-paths (node-sum t (node-l t)))
            (leaf))
          (node-elem t)
          (if (node? (node-r t))
            (sum-paths (node-sum t (node-r t)))
            (leaf) ))))
         
;_______________________________________________________________
;ZAD 4

(define (flatten2 t)          
  (define (flat-append t xs)
    (if (leaf? t)
        xs
        (flat-append
         (node-l t)
         (cons (node-elem t)(flat-append (node-r t) xs)))))
  (flat-append t null))

;_____________________________________________________________________
;ZAD 5

(define (insert-duplicate-bst x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond [(or (< x (node-elem t)) (= x (node-elem t)))
                (node
                 (insert-duplicate-bst x (node-l t))
                 (node-elem t)
                 (node-r t))]
               [else
                (node
                 (node-l t)
                 (node-elem t)
                 (insert-duplicate-bst x (node-r t)))])]))


(define (list-tree x xs t)
  (if (null? xs)
      t
      (insert-duplicate-bst (car xs) (list-tree x (cdr xs) t) )))

(define (treesort xs)
  (flatten2 (list-tree null (cdr xs) (node (leaf) (car xs) (leaf)))))

;_____________________________________________________________________
;ZAD 6

(define (find-min t)
  (if (leaf? (node-l t))
     (node-elem t)
     (find-min (node-l t))))

(define (delete x t)
  (cond [(= x (node-elem t))
      (if (leaf? (node-r t))
          (node-l t)
          (node
           (node-l t)
           (find-min (node-r t))
           (delete (find-min (node-r t)) (node-r t))))]
        [(< x (node-elem t))
         (node
          (delete x (node-l t))
          (node-elem t)
          (node-r t))]
        [else
         (node
          (node-l t)
          (node-elem t)
          (delete x (node-r t)))]))
;_______________________________________________________________
;ZAD7
(define empty-queue
   (cons '() '()))

(define (empty? q)
   (null? (car q)))

(define (push-back x q)
  (cons (car q) (list (cons x (cdr q)))))

(define (front q)
  (car(car q)))

(define (pop q)
  (if (null? (car(cdr q)))
      (reverse (cdr q))
      (car (cdr q))))



         
      
          
      
          
