;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test opérations
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

(define a -4)

(+ 5)
(+ 5 9)
(+ 5 3 4)
(+ a 6)

(* 6)
(* 4 2)
(* 2 5 9)
(* 8 a)

(- 10)
(- 2 3)
(- 3 4 5)
(- 8 a)

(/ 4)
(/ 11 9)
(/ 2 7 5)
(/ a 3)

(abs -7)
(abs 15)
(abs a)

(remainder 13 4)
(remainder -13 4)
(remainder 13 -4)
(remainder -13 -4)
(remainder a 2)

(= 4 4)
(= 2 3)
(= 3 5 10)
(= a 9)

(< 1 2)
(< 2 3 6)
(< 3 2 6)
(< a 15)

(> 3 6)
(> 9 5 1)
(> 9 10)
(> a 15)
