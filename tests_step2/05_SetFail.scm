;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT= test function set
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define toto 12)
(set! 12 3)


(define a 13)
(set! 13)
a

(define toto 12)
(set! toto a)
toto

(define toto 12)
(set! b 14)
toto
b
