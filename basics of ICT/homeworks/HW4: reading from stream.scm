(define (read-words)
  (define (reader port res cur)
    (let ((ch (peek-char port)))
      
      (cond
        ((eof-object? ch)
         (if (null? cur)
             (reverse res)
             (reverse (cons (list->string (reverse cur)) res))))

        ((char-whitespace? ch)
         (begin
           (read-char port)
           (if (null? cur)
               (reader port res cur)
               (reader port (cons (list->string (reverse cur)) res) '()))
           )
         )

        (else
         (reader port res (cons (read-char port) cur)))
        )))

  (reader (current-input-port) '() '())
  )

