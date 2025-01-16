(define (linear-equation a11 a12 a21 a22 b1 b2)
  (if (not (= 0 (- (* a11 a22) (* a12 a21))))
      (list
             (/ (- (* b1 a22) (* b2 a12)) (- (* a11 a22) (* a12 a21)))
             (/ (- (* a11 b2) (* a21 b1)) (- (* a11 a22) (* a12 a21)))
             )
      '()))
