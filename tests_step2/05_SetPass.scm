;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test function set
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define a 13)
(set! a 3)
a

(define b 14)
(set! b (and #t #f 6))
b



