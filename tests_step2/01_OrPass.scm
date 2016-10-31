;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT=test function or
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(or #t #f)
(or #f #t)
(or #t #t)
(or #f #f)

(or 12 3)
(or #t 4)
(or #f 23)

(define a 14)
(or a #t)

(or #t a 34)
(or #f 2 3)

(or #t (or #t #t))
(or #t (or #f #t))

(or #f (and #t #t) (or #t #f))

(and 1 2 (quote (feg) ))
