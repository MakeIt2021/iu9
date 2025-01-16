(define (uniq xs)
  (cond
    ((= 0 (length xs)) '())
    ((= 1 (length xs)) xs)
    ((equal? (car xs) (car (cdr xs))) (uniq (cdr xs)))
    (else (cons (car xs) (uniq (cdr xs))))))


(define (delete pred? xs)
  (cond
    ((null? xs) '())
    ((pred? (car xs)) (delete pred? (cdr xs)))
    (else (cons (car xs) (delete pred? (cdr xs))))))


(define (polynom ks x)
  (if (null? ks)
      0
      (+ (* (car ks) (expt x (- (length ks) 1))) (polynom (cdr ks) x))))


(define (intersperse e xs)
  (cond
    ((null? xs) '())
    ((= 1 (length xs)) xs)
    (else (cons (car xs) (cons e (intersperse e (cdr xs)))))))


(define (all? pred? xs)
  (or (= 0 (length xs)) (and (pred? (car xs)) (all? pred? (cdr xs)))))


(define (o . funcs)
  (lambda (x)
    (if (null? funcs)
        x
        ((car funcs) ((apply o (cdr funcs)) x)))))
