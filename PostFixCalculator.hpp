/*
Denysse Cunza
CSCI 23500
Project 7
*/

#pragma once
#ifndef PostfixCalculator_hpp
#define PostfixCalculator_hpp
#include <stack>
#include <string>
#include <iostream>


class PostfixCalculator
{
public:
    //Default constructor
    PostfixCalculator();
    
    //Helper Functions
    int hasPrecedence(char c);
    bool isOperator(char c);
    bool isBalanced(std::string s); 

    //Mandatory Functions
    std::string convertToPostfix(std::string infix_expression);
    double calculatePostfix(std::string postfix_expression);
    void testCalculator(std::string input_file_name);

  
private:
    std::stack<char> stackOperator;
};
#endif
