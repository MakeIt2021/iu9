(define pi (* 4 (atan 1)))

(define (my-abs x)
  ((if (> x 0) + -) x))

(define (my-even? x)
  (if (= 0 (remainder x 2)) #t #f))

(define (my-remainder a b)
  (if (< a b) a (my-remainder (- a b) b)))