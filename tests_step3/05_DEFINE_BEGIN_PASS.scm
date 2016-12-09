;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test DEFINE et BEGIN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 


(define a 34)

(begin (+ 5 6) (* 6 7))

(begin (+a 5) (* a a))
(begin (set! a 5)
(+ a 1))

(define (fois2 x) (* 2 x)) 
fois2
(fois2 3)
(fois2 (fois2 3))
(fois2 (fois2 (+ 3 34))


