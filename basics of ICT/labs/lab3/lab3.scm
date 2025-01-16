(define-syntax trace
  (syntax-rules ()
    ((trace expr)
     (let ((val expr))
       (write 'expr)
       (display " => ")
       (write val)
       (newline)
       val)
     )))


(define-syntax test
  (syntax-rules ()
    ((test call exp) (list 'call exp))))

(define (run-test test)
  (display (car test))
  (let ((retval (eval (car test) (interaction-environment))))
    (if (equal? retval (cadr test))
        (begin
          (display " ok")
          (newline)
          #t)
        (begin
          (display " FAIL")
          (newline)
          (display "  Expected: ")
          (write (cadr test))
          (newline)
          (display "  Returned: ")
          (write retval)
          (newline)
          #f
          ))))

(define (run-tests tests)
  (define (loop tests allpassed?)
    (if (null? tests)
        allpassed?
        (if (run-test (car tests))
            (loop (cdr tests) allpassed?)
            (loop (cdr tests) #f))))
  (loop tests #t))


(define (ref seq num . ins)
  (if (null? ins)
      (cond
        ((list? seq) (and (< num (length seq)) (list-ref seq num)))
        ((vector? seq) (and (< num (vector-length seq)) (vector-ref seq
                                                                    num)))
        ((string? seq) (and (< num (string-length seq)) (string-ref seq num))))
      (cond
        ((vector? seq)
         (let ((list-seq (vector->list seq)))
           (list->vector (ref list-seq num (car ins)))))
        ((string? seq)
         (or
          (and (char? (car ins)) (= (string-length seq) num)
               (string-append seq (string (car ins))))
          (and (char? (car ins))
               (not (= (string-length seq) num))
               (<= 0 num)
               (<= num (string-length seq))
               (let ((list-seq (string->list seq)))
                 (list->string (ref list-seq num (car ins)))))))
        ((list? seq)
         (if (and (<= 0 num) (<= num (length seq)))
             (cond
               ((null? seq) (list ins))
               ((= num 0) (cons (car ins) seq))
               (else (cons (car seq) (ref (cdr seq) (- num 1) (car ins))))))))))


(define (if->cond chain . nested?)
  (if (and (list? chain) (eq? (car chain) 'if))
      (let* ((condit (cadr chain))
             (true_branch (caddr chain))
             (false_branch (if (null? (cdddr chain)) #f (cadddr chain)))
             (cond-statement (list condit true_branch)))
        (if (eq? nested? '())
            (cons 'cond
                  (if (not false_branch)
                      (list cond-statement)
                    
                      (if (and (list? false_branch) (eq? (car false_branch)
                                                         'if))
                          (cons cond-statement
                                (if->cond false_branch #t))
                          (cons cond-statement
                                (list (cons 'else (cons false_branch
                                                        '())))))))
            (cond
              ((not false_branch) (cons cond-statement '()))
            
              ((and (list? false_branch) (eq? (car false_branch) 'if))
               (cons cond-statement
                     (if->cond false_branch #t)))
              (else
               (cons cond-statement
                     (list (cons 'else (cons false_branch '()))))))
            ))))
