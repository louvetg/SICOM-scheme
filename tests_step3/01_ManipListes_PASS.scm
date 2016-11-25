;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= Test manipulation de listes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

(cons 'a '())
(cons '(a)'(b c d))
(cons "a" '(b c))
(cons 'a 3)
(cons '(a b) 'c)

(car '(a b c))
(car '((a) b c d))
(car '(1 . 2))

(cdr '((a) b c d))
(cdr '(1 . 2))

(define paire (cons 1 3))
paire
(set-car! mypair 4)
(set-cdr! mypair 6)

(list 'a (+ 3 4) 'c)
(list)

