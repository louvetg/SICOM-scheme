;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test LAMBDA LET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

((lambda (x) (* x 2 )) 4)
((lambda ( x y ) (+ 5 (- x y )))  2 2)

((let (x 4) (* x 2 ))
(let ((x 2) (y 2)) (+ 5 (- x y )))
