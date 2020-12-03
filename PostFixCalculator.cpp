/*
Denysse Cunza
Project 7
CSCI 23500
*/
#include "PostfixCalculator.hpp"
#include "PrecondViolatedExcep.hpp"
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <cctype>


using namespace std;


PostfixCalculator::PostfixCalculator()
{
    //Constructor
}

bool PostfixCalculator::isOperator(char c)
{
    if(c == '*' || c == '-' || c == '+' || c == '/')
    {
        return true;
    }
    
    return false;
    
}

int PostfixCalculator::hasPrecedence(char c)
{
    if(c == '*' || c == '/')
    {
        return 2;
    }
    else if(c == '+' || c == '-')
    {
        return 1;
    }
    return -1;
}

bool PostfixCalculator::isBalanced(string s)
{
    int brackets = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == '(')
            brackets += 1;
        if(s[i] == ')')
            brackets -= 1;
    }
    if(brackets == 0)
    {
        return true;
    }
    return false;
}


string PostfixCalculator::convertToPostfix(string infix_expression)
{
    stack<char> nStack;
    string postFix = "";
    char ch;
    for (int i = 0; i < infix_expression.length(); i++)
    {
        ch = infix_expression[i];

        switch (ch)
        {
            // all types of digits
            case '0': // append operand to end of postfix expression
          	case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
          	case '8': 
          	case '9':
            	// add the first character of the integer
            	postFix += ch;
                // while next character is a digit
            	while (isdigit(infix_expression[i+1]) )
                {
                    // append next digit of integer
                	postFix += infix_expression[i+1];
                    i++;
                }
            	// put space after operand
            	postFix += " "; 	
                break;

            case '(':
                nStack.push(ch);
                break;

            case '+':
         	case '-':
          	case '*':
         	case '/':
            	// pop off the stack until we get to a closing parentheses or a operator with higher precedence
                while (!nStack.empty() && (nStack.top() != '(') && (hasPrecedence(ch) <= hasPrecedence(nStack.top())) ) 
                {
                  	// add it to expression all of the parts
                	postFix += nStack.top();
                  	nStack.pop();
                  	postFix += " ";
                }
                nStack.push(ch); // add the operator
            	break;

            case ')': // pop stack until matching '(' - step 4
            
                while(nStack.top() != '(' )
                {
                    postFix += nStack.top();
                    nStack.pop();
                  
                  	postFix += " ";
                    
                    if (nStack.empty())
                    {
                        throw (PrecondViolatedExcep("Unbalanced parenthesis") );
                        break;
                    }
                }
                nStack.pop();      
                break;

            case ' ':
            case '\n':
            case '\r':
            	break; 
                
            default: // if it is not a digit, space, parentheses, or basic operator
                    throw ( PrecondViolatedExcep("Unknown operator") ); // throw error
                    break;     
        }
    }
    
    // append to postFix the operators remaining in the stack 
    while(!nStack.empty())
    {
        // if any start parentheses were left on the stack
        if (nStack.top() == '(')
        {
            // cout << "extra starting parentheses" << endl;
            throw ( PrecondViolatedExcep("Unbalanced parenthesis") );
        }
        
        postFix += nStack.top();
        nStack.pop();
      
      	postFix += " ";
    }
    
    return postFix;

}


double PostfixCalculator::calculatePostfix(string postfix_expression)
{
    stack<double> newStack;
  	char c; 
    for(int i = 0; i < postfix_expression.length(); i++)
    {
   		c = postfix_expression[i];
      	// if it is an operator
        if ( (c == '+') || (c == '-') || (c == '*') || (c == '/') )
        {
            double result = 0;
            double op2 = newStack.top();
            newStack.pop();
            double op1 = newStack.top();
            newStack.pop();
            
          	// check which operator we are using
            if (c == '+')
            	result = op1 + op2; 
            else if (c == '-')
              	result = op1 - op2; 
            else if (c == '*')
              	result = op1 * op2; 
            else if (c == '/')
              	result = op1 / op2; 
            
			// push the result on the stack
            newStack.push(result);
        }
      	else if (isdigit(c))     // if it is a operand 
      	{ 
            // initialize empty string
            string nString = "";
            // add first caracter
            nString += c;
            // while there are more digits
            while ( isdigit(postfix_expression[i+1]) )
            {
                // append next digit of integer
                nString += postfix_expression[i+1];
                i++;
            } 
            double num = atof(nString.c_str());
            newStack.push(num);
        }
    }
    return newStack.top();
}



void PostfixCalculator::testCalculator(string input_file_name)
{
  	// input file stream and output file stream
    ifstream inFile;
  
    ofstream file1;
    file1.open("postfix.txt");
    
    ofstream file2;
    file2.open("results.txt");
    
    // inFile.open("input.txt");
    
  	inFile.open(input_file_name);
  
    if (inFile.fail()) 
    {
    	cout << "Error opening a file" << endl;
    	inFile.close();
    }
  	
 	 // go row by row through the file
    string row;
    while (getline(inFile, row))
    {
        try // try to convert to postfix
        {
        	//cout << convertToPostfix(row) << endl;
          	file1 << convertToPostfix(row) << endl;
           
          	//cout << calculatePostfix(convertToPostfix(row)) << endl;
            file2 << calculatePostfix(convertToPostfix(row)) << endl;
          
        }
        catch (PrecondViolatedExcep& e)
   		{
            //cout  << e.what() << endl;
            file1 << e.what() << endl;
            file2 << e.what() << endl;
    	}
       
    }
  	inFile.close();
  	file1.close();
  	file2.close();
}
