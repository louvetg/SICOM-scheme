;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test quote
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(quote(45))
(quote (a))
(quote(3 4 5))
(quote ((34 5)))

(define b 10)
(quote b)

'(2 6)
'((or #t 4))
(quote (and (#t #t)))

