// File: infix_expression.h
// Created by holger on 2020/10/1.
// The definition of Class InfixExpression

#ifndef INFIX_EXPRESSION_INFIX_EXPRESSION_H
#define INFIX_EXPRESSION_INFIX_EXPRESSION_H

#include <iostream>
#include <sstream>
#include <string>
#include "container/sequence_stack.hpp"

// The infix expression class
class InfixExpression {
public:
    static void showDetail(bool = false) noexcept;   // show detail when calculating
    explicit InfixExpression(std::string);  // Initialize the expression with a string object.
    double calculate();    // Get the result of the expression, throw std::runtime_error when expression is invalid
private:
    std::string expression; // the infix expression without blank
    Stack<char> operators;  // the stack of operators
    Stack<double> operands; // the stack of operands
    static bool detail;     // determine whether show detail when calculating
    // The following are auxiliary functions defined to simplify the process of calculate:
    void calculateNext();   // Get one operator and do calculation.
    void getOperands(double &, double &);  // Left and right operand pop out of stack
    void saveOperand(double);  // Result operand push into stack
    char &getOperator(char &);  // top operator pop out of stack
    void saveOperator(char);    // operator push into stack
    double /* CALLBACK */ getResult();    // Check the status when the calculation is complete and get the result
    static void matchBracketCheck(const std::string &);  // Check the brackets match
    static std::string parseExpression(const std::string &);  // Parse expressions for calculation
    static int operatorCompare(char, char) noexcept;   // Compare operator precedence
    static double digitCompute(double, char, double);    // Do compute: `left op right`
    static bool isDigitString(const std::string &) noexcept;   // Determine whether the string is a float number
    static void
    splitOperatorsOperands(std::string &) noexcept; // Add blanks between operands and operators to split.
    static bool isValidChar(char ch) noexcept;   // Check invalid characters.
    static void determineMinus(std::string &, int) noexcept;   // Change '-'(means 'minus') to '~'
};

#endif //INFIX_EXPRESSION_INFIX_EXPRESSION_H
