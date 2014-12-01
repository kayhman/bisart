(format t "I've run the contents of init.lisp~%")
 
(defun foo ()
    (format t "We called foo...~%"))

(require :asdf)
(require :ecl-quicklisp)
