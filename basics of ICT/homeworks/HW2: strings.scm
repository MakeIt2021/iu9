; O(n)
(define (string-trim-left in)
  (define (trimmer s)
    (if (char-whitespace? (car s))
        (trimmer (cdr s))
        (list->string s)
        )
    )
  (trimmer (string->list in))
  )


; O(n)
(define (string-trim-right in)
  (define (trimmer s)
    (if (char-whitespace? (car s))
        (trimmer (cdr s))
        (list->string (reverse s))
        )
    )
  (trimmer (reverse (string->list in)))
  )


; O(n)
(define (string-trim in)
  (string-trim-left (string-trim-right in)))


; O(n)
(define (string-prefix? st1 st2)
  (define (comparator s1 s2)
    (or (null? s1)
        (and (not (null? s2))
             (equal? (car s1) (car s2))
             (comparator (cdr s1) (cdr s2)))
        )
    )
  (comparator (string->list st1) (string->list st2))
  )


; O(n)
(define (string-suffix? st1 st2)
  (string-prefix? (list->string (reverse (string->list st1))) (list->string (reverse (string->list st2)))))


; O(n^2)
(define (string-infix? st1 st2)
  (and (not (= 1 (string-length st2)))
       (not (and (not (= 0 (string-length st1))) (= 0 (string-length st2))))
       (or (string-prefix? st1 st2)
           (string-infix? st1 (list->string (cdr (string->list st2)))))))


; O(n)
(define (match-sep? str sep)
  (cond
    ((null? sep) #t)
    ((null? str) #f)
    ((equal? (car str) (car sep))
     (match-sep? (cdr str) (cdr sep)))
    (else #f)
    )
  )

; O(n)
(define (multi-cdr str nel)
  (if (= nel 0)
      str
      (multi-cdr (cdr str) (- nel 1))))

; O(n^2)
(define (string-split str sep)
  (define (splitter res cur str sep)
    (if (null? str)
        (reverse (cons (list->string cur) res))
        (if (match-sep? str sep)
            (splitter (cons (list->string (reverse cur)) res) '() (multi-cdr str (length sep)) sep)
            (splitter res (cons (car str) cur) (cdr str) sep))))
  (splitter '() '() (string->list str) (string->list sep)))

