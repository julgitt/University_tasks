#lang racket




(define-struct column-info (name type) #:transparent)

(define-struct table (schema rows) #:transparent)

(define cities
  (table
   (list (column-info 'city    'string)
         (column-info 'country 'string)
         (column-info 'area    'number)
         (column-info 'capital 'boolean))
   (list (list "Wrocław" "Poland"  293 #f)
         (list "Warsaw"  "Poland"  517 #t)
         (list "Poznań"  "Poland"  262 #f)
         (list "Berlin"  "Germany" 892 #t)
         (list "Munich"  "Germany" 310 #f)
         (list "Paris"   "France"  105 #t)
         (list "Rennes"  "France"   50 #f))))

(define countries
  (table
   (list (column-info 'country 'string)
         (column-info 'population 'number))
   (list (list "Poland" 38)
         (list "Germany" 83)
         (list "France" 67)
         (list "Spain" 47))))

(define (empty-table columns) (table columns '()))

; Wstawianie

(define (table-insert row tab)
  (define (compare a b) 
    (cond
      [(and (null? a) (null? b)) #t]
      [(or (null? a) (null? b)) #f]
      [(and (number? (car a)) (number? (car b)))
       (compare (cdr a)(cdr b))]
      [(and (string? (car a)) (string? (car b)))
       (compare (cdr a)(cdr b))]
      [(and (boolean? (car a)) (boolean?(car b)))
       (compare (cdr a)(cdr b))]
      [(and (symbol? (car a)) (symbol?(car b)))
       (compare (cdr a)(cdr b))]
      [else #f])) 
  (if(compare row (car(table-rows tab)))
     (table (table-schema tab) (cons row (table-rows tab)))
     "error"))


; Projekcja

 (define (find column tab info rows)
   (if (null? (car(table-schema tab)))
       (table info rows)
       (if (equal? column (column-info-name (car(table-schema tab))))
           (table (cons (car (table-schema tab)) info)
                  (if (null? rows)
                       (map list (map car (table-rows tab)))
                       (map cons (map car (table-rows tab)) rows)))
           (find column (table (cdr (table-schema tab)) (map cdr (table-rows tab))) info rows))))
    
(define (table-project cols tab)
  (define (create cols tab result)
    (if (null? cols) result
        (create (cdr cols) tab (find (car cols) tab (table-schema result) (table-rows result)))))
  (create (reverse cols) tab (table null null)))

; Zmiana nazwy
(define (table-rename col ncol tab)
   (define (change column name tab result)
     (if (null? (car tab)) result
         (if (equal? column (column-info-name (car tab)))
             (if (null? result)
                 (cons (column-info name (column-info-type (car tab)))
                       (cdr tab))
                 (cons result
                       (cons (column-info name (column-info-type (car tab)))
                             (cdr tab))))              
           (change column name (cdr tab)
                   (if (null? result)
                       (list (car tab))
                       (cons result (car tab)))))))
  (table (change col ncol (table-schema tab) null)
         (table-rows tab)))
;
;Sortowanie
(define (insert column row tab result)
    (if (null? result) (list row)
        (if (null? column) (append result (list row))  
            (let ([type (take-type (car column) (table-schema tab))]
                  [value1 (take-value (car column) row (table-schema tab))]
                  [value2 (take-value (car column) (car result) (table-schema tab))])
              (if (equal? value1 value2)
                  (append (insert (cdr column) row tab (list(car result))) (cdr result))
                  (if (cond
                        [(equal? 'string type)
                         (string<? value2 value1)]
                        [(equal? 'number type)
                         (< value2 value1)]
                        [(equal? 'symbol type)
                         (symbol<? value2 value1)]
                        [(equal? 'boolean type)
                         (if (and (not value2) value1)
                             #t #f)])
                      (cons (car result) (insert column row tab (cdr result)))
                      (cons row result)))))))
 
(define (insertion-sort column rows tab)
  (define (it column rows tab result)
             (if (null? rows)
                 result
                (it column (cdr rows) tab (insert column (car rows) tab result))))
  (it column rows tab null))

(define (sort-rows column tab) 
  (table (table-schema tab)
         (insertion-sort column (table-rows tab) tab)))
      
         

;Selection

(define-struct and-f (l r))
(define-struct or-f (l r))
(define-struct not-f (e))
(define-struct eq-f (name val))
(define-struct eq2-f (name name2))
(define-struct lt-f (name val))

(define (table-select form tab)
  (table (table-schema tab) (select form (table-rows tab) tab)))

(define (take-value name row schema)
  (if (null? schema) null
      (if (equal? name (column-info-name (car schema)))
          (car row)
          (take-value name (cdr row) (cdr schema)))))

(define (take-type name schema)
  (if (null? schema) null
      (if (equal? name (column-info-name (car schema)))
          (column-info-type (car schema))
          (take-type name (cdr schema)))))
          
(define (select form rows tab)
  (cond [(and-f? form)
         (select (and-f-l form)
                 (select  (and-f-r form) rows tab) tab)]
        [(or-f? form)
         (cons (select (or-f-r form) rows tab)
               (select (or-f-l form) rows tab))]
        [(not-f? form)
         (filter (lambda (x)(not (member x (select (not-f-e form) rows tab)))) rows)]
        [(eq-f? form)
         (filter (lambda (x) (equal?
                              (eq-f-val form)
                              (take-value (eq-f-name form) x (table-schema tab))))rows)]
        [(eq2-f? form)
         (filter (lambda (x) (equal?
                              (take-value (eq2-f-name2 form) x (table-schema tab))
                              (take-value (eq2-f-name form) x (table-schema tab))))rows)]
        [(lt-f? form)
         (filter (lambda (x) (cond
                               [(equal? 'string (take-type (lt-f-name form)(table-schema tab)))
                                (string<?
                                 (take-value (lt-f-name form) x (table-schema tab))
                                 (lt-f-val form))]
                               [(equal? 'number (take-type (lt-f-name form)(table-schema tab)))
                                (<
                                 (take-value (lt-f-name form) x (table-schema tab))
                                 (lt-f-val form))]
                                [(equal? 'symbol (take-type (lt-f-name form)(table-schema tab)))
                                (symbol<?
                                 (take-value (lt-f-name form) x (table-schema tab))
                                 (lt-f-val form))]
                               [(equal? 'boolean (take-type (lt-f-name form)(table-schema tab)))
                                (if (and (not (lt-f-val form)) (take-value (lt-f-name form) x (table-schema tab)))
                                    #t #f)])) rows)]))
;Laczenie Kartezjanskie
(define (join tab1 tab2 current-tab2 result)
  (cond [(null? tab1) result]
                 [(null? current-tab2) (join tab1 tab2 tab2 result)]
                 [else (join (cdr tab1) tab2 (cdr current-tab2)
                             (append result (list(append (car tab1)(car current-tab2)))))]))

(define (join2 tab1 tab2 current-tab1 result)
  (cond [(null? tab2) result]
                 [(null? current-tab1) (join2 tab1 tab2 tab1 result)]
                 [else (join2 tab1 (cdr tab2) (cdr current-tab1)
                             (append result (list(append (car current-tab1)(car tab2)))))]))
  
(define (table-cross-join tab1 tab2)
  (table (append (table-schema tab1) (table-schema tab2))
         (if (< (length (table-rows tab1)) (length (table-rows tab2)))
             (join2 (table-rows tab1) (table-rows tab2) (table-rows tab1) null)
             (join (table-rows tab1) (table-rows tab2) (table-rows tab2) null))))

        

;Zlaczenie Naturalne

(define (changing-names tab1 tab2)
  (define (help tab1 tab2 current)
    (if (null? current)
        tab2
        (if (member (car current) (table-schema tab1))
            (help tab1 (table-rename (column-info-name (car current))
                                     (string->symbol(string-append (symbol->string (column-info-name (car current)))"!"))
                                     tab2) (cdr current))
            (help tab1 tab2 (cdr current)))))
  (help tab1 tab2 (table-schema tab2)))

(define (find-name tab1 tab2)
  (cond [(null? tab1) null]
        [(null? tab2) null]
        [(equal? (string->symbol(string-append (symbol->string (column-info-name (car tab1))) "!")) (column-info-name (car tab2)))
         (column-info-name (car tab1))]
        [else (find-name (cdr tab1) (cdr tab2))]))

(define (select-rows result-table tab-changed-name tab)
  (let ([name (find-name (table-schema tab) (table-schema tab-changed-name))])
        (table-select (eq2-f name (string->symbol(string-append (symbol->string name) "!"))) result-table)))
                                 

(define (table-natural-join tab1 tab2)
  (table-project (columns (table-schema (select-rows (table-cross-join tab1 (changing-names tab1 tab2))
                                       (changing-names tab1 tab2) tab2))
                          (table-schema tab2) (table-schema (changing-names tab1 tab2)))
                 (select-rows (table-cross-join tab1 (changing-names tab1 tab2))
                                       (changing-names tab1 tab2) tab2)))

(define (columns result-tab tab tab-changed-name)
  (let ([name (find-name tab  tab-changed-name)])
    (filter (lambda (x)(not (equal? x (string->symbol(string-append (symbol->string name) "!")))))
            (map (lambda (y)(column-info-name y)) result-tab))))
  
                                
                              
                             
                 
  
  
   
    
           
