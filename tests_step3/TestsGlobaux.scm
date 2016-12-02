;;;;;;;;;;;;;;;; Script de test ;;;;;;;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT= test manipulation de listes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 

(define a     (* 6
                         7))
a

(cons '(a) '(b c d))

(list? '(a b c)) 

(symbol->string
            (string->symbol "Test"))

(eq? ’TestT              (string->symbol
(symbol->string ’TestT))) 

(eq? 'mISSISSIppi 'mississippi)

(eq? ’blaBla (string->symbol "blaBla"))

(/ (* (+ 3 4 5) 5 6 10) 45)

(integer? 8/4)

(define x (list ’a ’b ’c))
(define y x)
y
(list? y)
(set-cdr! x 4)
x 
(eqv? x y)
y
(list? y)
(set-cdr! x x)
(list? x)
