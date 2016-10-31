;;;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test function and/or/quote/define/set!/if
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(if (and #t #f) 'a )
(if (and #t #f) 'a 'b)
(if (and (or (and #t #t) #t) 1) "toto" "tata")
(if (and "toto" #f) "toto" "tata")

(define a #t)
(if a 1 0)
(set! a #f)
(if a 1 0)

(if #t (define b 2))
b
