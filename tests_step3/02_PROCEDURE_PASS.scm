;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test PROCEDURE?
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

(procedure? car)
(procedure? '(car))
(procedure? (lambda (x) (* x x)))
(procedure? '(lambda (x) (* x x)))

