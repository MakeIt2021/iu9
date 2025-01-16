; Обычно на лабах спрашивали, но для собственного понимания напишу:
; ` --- квазицитирование
; , --- надо вычислить выражение
; ,@ --- вычислить и вставить как элементы списка

(define (derivative expr)
  (cond
    ((number? expr) 0)
    
    ((equal? expr 'x) 1)

    ((and (pair? expr) (equal? (car expr) '+))
     `(+ ,(derivative (cadr expr)) ,(derivative (caddr expr)))
     )

    ((equal? expr '-x) -1)
    
    ((and (pair? expr) (equal? (car expr) '-) (null? (cddr expr)))
     `(- ,(derivative (cadr expr))))

    ((and (pair? expr) (equal? (car expr) '-) (pair? (cddr expr)))
     `(- ,(derivative (cadr expr)) ,(derivative (caddr expr))))
    
    ((and (pair? expr) (equal? (car expr) '*))
     (let loop ((terms (cdr expr)) (result '()))
       (if (null? terms)
           (if (null? result)
               0
               `(+ ,@result))
           (let ((current-term (car terms)))
             (loop (cdr terms)
                   (cons `(* ,(derivative current-term)
                             ,@(remove-element current-term (cdr expr))) result))))))

    
    ((and (pair? expr) (equal? (car expr) '/))
     (let ((u (cadr expr))
           (v (caddr expr)))
       `(/ (- (* ,(derivative u) ,v) (* ,u ,(derivative v))) (expt ,v 2))
       ))

    ((and (pair? expr) (equal? (car expr) 'expt))
     (let ((base (cadr expr))
           (power (caddr expr)))
       (if (number? power)
       `(* ,power (expt ,base ,(- power 1)))
       `(* (expt ,base ,power) (+ (* ,(derivative base) (/ ,power ,base))
                  (* (log ,base) ,(derivative power)))))))

    
    ((and (pair? expr) (equal? (car expr) 'sin))
     `(* (cos ,(cadr expr)) ,(derivative (cadr expr))))

    ((and (pair? expr) (equal? (car expr) 'cos))
     `(- (* (sin ,(cadr expr)) ,(derivative (cadr expr)))))

    ((and (pair? expr) (equal? (car expr) 'exp))
     `(* ,(derivative (cadr expr)) (exp ,(cadr expr))))

    ((and (pair? expr) (equal? (car expr) 'log))
     (let ((arg (cadr expr)))
       `(/ ,(derivative arg) ,arg)))
  )
  )
  
(define (remove-element elem lst)
  (cond
    ((null? lst) '())
    ((equal? (car lst) elem) (cdr lst))
    (else (cons (car lst) (remove-element elem (cdr lst))))))
