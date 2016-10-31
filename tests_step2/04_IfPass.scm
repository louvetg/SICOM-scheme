;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test function if
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(if (or #t #f) (quote (#f)) (quote (#t)))
(if (and #t #f) (quote (#f)) (quote (#t)))

(define a 23)
(if (or #t #f) a (quote #t))
