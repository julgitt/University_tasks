#lang racket

(define (good_move? place board n)
  (and (good_cordinate? place n) (is_free? place board)))

(define (good_cordinate? place n)
  (let ([first (car place)] [second (cdr place)])
    (and (<= 1 first)
         (<= first n)
         (<= 1 second)
         (<= second n))))

(define (is_free? place board)
  (cond
    [(null? board) #t]
    [(equal? place (car board)) #f]
    [else (is_free? place (cdr board))]))

(define (knight n)
  (define (knights_tour  move_to_end  begin_place  board)
    (if (= move_to_end 0)
        board
        (or
          (let ([new_place (cons (- (car begin_place) 1) (- (cdr begin_place) 2))])
          (if (good_move? new_place board n)
              (knights_tour (- move_to_end 1) new_place (append (list new_place) board))
              #f))
          (let ([new_place (cons (- (car begin_place) 2) (- (cdr begin_place) 1))])
          (if (good_move? new_place board n)
              (knights_tour (- move_to_end 1) new_place (append (list new_place) board))
              #f))
          (let ([new_place (cons (- (car begin_place) 2) (+ (cdr begin_place) 1))])
          (if (good_move? new_place board n)
              (knights_tour (- move_to_end 1) new_place (append (list new_place) board))
              #f))
          (let ([new_place (cons (- (car begin_place) 1) (+ (cdr begin_place) 2))])
          (if (good_move? new_place board n)
              (knights_tour (- move_to_end 1) new_place (append (list new_place) board))
              #f))
          (let ([new_place (cons (+ (car begin_place) 1) (+ (cdr begin_place) 2))])
          (if (good_move? new_place board n)
              (knights_tour (- move_to_end 1) new_place (append (list new_place) board))
              #f))
          (let ([new_place (cons (+ (car begin_place) 2) (+ (cdr begin_place) 1))])
          (if (good_move? new_place board n)
              (knights_tour (- move_to_end 1) new_place (append (list new_place) board))
              #f))
          (let ([new_place (cons (+ (car begin_place) 2) (- (cdr begin_place) 1))])
          (if (good_move? new_place board n)
              (knights_tour (- move_to_end 1) new_place (append (list new_place) board))
              #f))
          (let ([new_place (cons (+ (car begin_place) 1) (- (cdr begin_place) 2))])
          (if (good_move? new_place board n)
              (knights_tour (- move_to_end 1) new_place (append (list new_place) board))
              #f)))))
  (knights_tour (- (* n n) 1) (cons 1 1) (list (cons 1 1))))
  


