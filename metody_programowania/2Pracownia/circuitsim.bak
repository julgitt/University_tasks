#lang racket
(require data/heap)
(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]
          [sim-add-action! (-> sim? positive? (-> any/c) void?)]

          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]
          [wire-set!       (-> wire? boolean? void?)]

          [bus-value (-> (listof wire?) natural?)]
          [bus-set!  (-> (listof wire?) natural? void?)]

          [gate-not  (-> wire? wire? void?)]
          [gate-and  (-> wire? wire? wire? void?)]
          [gate-nand (-> wire? wire? wire? void?)]
          [gate-or   (-> wire? wire? wire? void?)]
          [gate-nor  (-> wire? wire? wire? void?)]
          [gate-xor  (-> wire? wire? wire? void?)]

          [wire-not  (-> wire? wire?)]
          [wire-and  (-> wire? wire? wire?)]
          [wire-nand (-> wire? wire? wire?)]
          [wire-or   (-> wire? wire? wire?)]
          [wire-nor  (-> wire? wire? wire?)]
          [wire-xor  (-> wire? wire? wire?)]

          [flip-flop (-> wire? wire? wire? void?)]))

;____________________________SIMULATION____________________________

(struct sim ([current-time #:mutable] [event-queue #:mutable]))

(struct action ([time #:mutable] [function #:mutable]))

(define (action<=? a1 a2)
  (< (action-time a1)(action-time a2)))

(define (make-sim)
  (sim 0.0 (make-heap action<=?)))

(define (sim-time sim) ;getter
  (sim-current-time sim))


(define (sim-wait! sim time)
  (begin
    (set-sim-current-time! sim (+ (sim-time sim) time))
    (call-event-queue (sim-event-queue sim))))

(define (call-event-queue events-heap sim)
  (cond
    [(equal? (heap-count events-heap) 0) ;jeżeli kolejka zdarzeń jest pusta
      (void)]
    [(<= (action-time (heap-min events-heap)) (sim-time sim)) ;jeżeli czas jakiejś akcji upłynął
     (begin
       (action-function (heap-min events-heap)) ;wywołujemy funcję
       (heap-remove-min! events-heap) ;usuwamy ją z kolejki
       (call-event-queue events-heap))] ;sprawdzamy dla reszty akcji
    [else (void)]))
     
(define (sim-add-action! sim time f)
  (set-sim-event-queue! sim (heap-add! (sim-event-queue sim) (action time f))))

;____________________________WIRE__________________________________

(struct wire ([value #:mutable] [sim  #:mutable] [actions #:mutable]))

(define (make-wire sim)
  (wire #f sim (make-heap action<=?)))

(define (wire-on-change! wire f)
  (begin
    (f) ;wywołujemy akcję
    (set-wire-actions! wire (cons f (wire-actions wire))))) ; dodajemy akcję do listy akcji przewodu

(define (call-actions xs)
  (if (null? xs)
      (void)
      (begin
        ((car xs))
        (call-actions (cdr xs)))))

(define (wire-set! wire value) ;setter przewodu
  (if (eq? value (wire-value wire))
      (void)
      (begin
        (set-wire-value! wire value)
        (call-actions (wire-actions wire)))))

  ;_________________________________BUS________________________________

(define (bus-set! wires value) ;setter magistrali
  (match wires
    ['() (void)]
    [(cons w wires)
     (begin
       (wire-set! w (= (modulo value 2) 1)) ;?
       (bus-set! wires (quotient value 2)))]))

(define (bus-value ws) ;getter?
  (foldr (lambda (w value) (+ (if (wire-value w) 1 0) (* 2 value)))
         0
         ws))

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))

  ;_________________________________GATES________________________________

(define (gate-not out in)
  (sim-add-action! (wire-sim out) 1.0 (wire-on-change! in (wire-set! out (not (wire-value in))))))

(define (gate-and out in1 in2)
  (define and-action
    (wire-set! out (and (wire-value in1)(wire-value in2))))
  (sim-add-action! (wire-sim out) 1.0 (begin
                                       (wire-on-change! in1 and-action)
                                       (wire-on-change! in2 and-action))))

(define (gate-nand out in1 in2)
  (define (nand-action)
    (wire-set! out (not (and (wire-value in1) (wire-value in2)))))
  (sim-add-action! (wire-sim out) 1.0 (and
                                       (wire-on-change! in1 nand-action)
                                       (wire-on-change! in2 nand-action))))

(define (gate-or out in1 in2)
  (define or-action
    (wire-set! out (or (wire-value in1)(wire-value in2))))
  (sim-add-action! (wire-sim out) 1.0 (and
                                       (wire-on-change! in1 or-action)
                                       (wire-on-change! in2 or-action))))

(define (gate-nor out in1 in2)
   (define nor-action
    (wire-set! out (not (or (wire-value in1)(wire-value in2)))))
  (sim-add-action! (wire-sim out) 1.0 (and
                                       (wire-on-change! in1 nor-action)
                                       (wire-on-change! in2 nor-action))))


(define (gate-xor out in1 in2) ;and (or)(nand)
(define xor-action
    (wire-set! out (and (or (wire-value in1)(wire-value in2))
                        (not(and (wire-value in1)(wire-value in2))))))
  (sim-add-action! (wire-sim out) 2.0 (and
                                       (wire-on-change! in1 xor-action)
                                       (wire-on-change! in2 xor-action))))

  ;_________________________________WIRE-GATES________________________________
;(struct wire ([value #:mutable] [sim  #:mutable] [actions #:mutable]))

(define (wire-not in)
  (define out
    (make-wire (wire-sim in)))
  (gate-not out in)
  out)

(define (wire-and in1 in2)
  (define out
    (make-wire (wire-sim in1)))
  (gate-and out in1 in2)
  out)


(define (wire-nand in1 in2)
    (define out
      (make-wire (wire-sim in1)))
  (gate-nand out in1 in2)
  out)


(define (wire-or in1 in2)
   (define out
      (make-wire (wire-sim in1)))
  (gate-or out in1 in2)
  out)

(define (wire-nor in1 in2)
 (define out
      (make-wire (wire-sim in1)))
  (gate-nor out in1 in2)
  out)

(define (wire-xor in1 in2)
  (define out
      (make-wire (wire-sim in1)))
  (gate-xor out in1 in2)
  out)

