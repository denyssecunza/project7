Project7- Class CSCI 235
//  Created by Tiziana Ligorio 
//  Course project, Hunter Collegge, CSci 235 - Software Design and Analysis II
//  Copyright © 2019 Tiziana Ligorio. All rights reserved.

Postfix Calculator

For this project you will implement a simple calculator. Your calculator is going to parse infix algebraic expressions, create the corresponding postfix expressions and then evaluate the postfix expressions. The operators it recognizes are: +, -, * and /. The operands are integers.
Your program will either evaluate individual expressions or read from an input file that contains a sequence of infix expressions (one expression per line). When reading from an input file, the output will consist of two files: postfix.txt that contains the corresponding postfix expressions one per line and results.txt that contains their evaluation, also one per line.
An example of an infix expression is the following:
( 12 + 3 ) * ( 9 – 74 ) + 34 / ( ( 85 – 93 ) + ( 3 + 5 ) * 3 ) - 5  
It is guaranteed to:
• Contain only integers
• Contain only round parentheses
• All operands and operators are separated by a single space 
A malformed expression may however:
• Have unbalanced parentheses — e.g. ( ( ( 3 + 2 )
• Have operators other than the expected ones — e.g 2 ^ 3 
   
Your program will parse the infix expression from left to right, identify the operands, the operators and the parentheses and ignore blanks. You will implement the infix to postfix conversion algorithm using a stack of operators and parentheses. You can use the STL stack (#include <stack>)
Your program should handle syntactically malformed infix expressions using exceptions (you can use the PrecondViolatedExcep class used with the List class — see Project4). When an exception occurs, the exception message should be written to the postfix file and results file instead of the respective postfix expression and result. For unbalanced parenthesis the message must be:
“Precondition Violated Exception: Unbalanced parenthesis”
For unknown operator the message must be:
“Precondition Violated Exception: Unknown operator”
An example of a correct infix expression
( 12 + 3 ) * ( 9 – 74 ) + 34 / ( ( 85 – 93 ) + ( 3 + 5 ) * 3 ) - 5

An example of an expression with unbalanced parenthesis
( ( ( 3 + 2 ) 
or
( 3 + 2 ) )

An example of unknown operator
( 2 + 3 ) ^ 2
