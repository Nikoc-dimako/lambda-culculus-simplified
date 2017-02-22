This program is written in C++ , it takes a complex lambda culcurus expression and converts it to its normal form. 

λ : \
lambda culcurus expression :  \x.\y.x

compile : make lambda

Execution example : ./lambda "((\Zz.Zz (\x.\y.y)) ((\  xx  .\y.\z.z xx y) N M) )"
stdout : input=((\Zz.Zz (\x.\y.y)) ((\  xx  .\y.\z.z xx y) N M) )
         result=M
         
 The program is developed in the context of "Principles of Programming Languages" course. The Lambda expression is given as a
 parameter to executable call and it's enclosed by "". Unfortunately, expressions that contain numbers, do not print the right result due to
 the program can't elaborate the term f(x).
 

