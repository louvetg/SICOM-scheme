;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test function and
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(and #t #f)
(and #f #t)
(and #t #t)
(and #f #f)

(and 12 3)
(and #t 4)
(and #f 23)

(define a 14)
(and a #t)

(and #t a 34)
(and #f 2 3)

(and #t (and #t #t))
(and #t (and #f #t))

(and #t (and #t #t) (or #t #f))

(and 1 2 ’c ’(f g)) 
