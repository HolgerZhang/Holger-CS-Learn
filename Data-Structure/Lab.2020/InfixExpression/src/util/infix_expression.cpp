// File: infix_expression.cpp
// Created by holger on 2020/10/1.
// The implement of Class InfixExpression

#include "infix_expression.h"

bool InfixExpression::detail = false;   // determine whether show detail when calculating

/**
 * Show detail when calculating.
 * @param param set field InfixExpression::detail
 */
void InfixExpression::showDetail(bool param) noexcept {
    InfixExpression::detail = param;
}

/**
 * Initialize the expression with a string object.
 * @post    Erase the blank and character '#' in the expression (if it has).
 * @param str The string contained the infix expression.
 */
InfixExpression::InfixExpression(std::string str) : expression(std::move(str)), operators(), operands() {
    auto p = expression.begin();
    while (p != expression.end()) { // erase the blank and '#' (if has)
        if (*p == ' ' || *p == '#') { p = expression.erase(p); }
        else { ++p; }
    }
}

/**
 * Public method of expression calculation.
 * @pre     The expression object is a valid infix expression of float number.
 * @return  The result of the expression.
 */
double InfixExpression::calculate() {
    /* Pre: make sure stacks are empty */
    operands.clear(), operators.clear();   // Clear the stacks

    /* STEP1: Expression Legality Check, Split. */
    if (detail) { std::cout << " $ Checking the bracket matching of the expression..." << std::endl; }
    matchBracketCheck(expression); // Check the brackets match
    // Parse the expression, and use string stream to split the parsed expression
    if (detail) { std::cout << " $ Parsing the expression..." << std::endl; }
    std::istringstream scanner(parseExpression(expression));
    if (detail) { std::cout << " * Got parsed expression: " << scanner.str() << std::endl; }

    /* STEP2: Save the Operators and Operands, and Do Easy Calculation. */
    std::string nextString; // Each part of expression
    while (scanner >> nextString) {
        if (detail) { std::cout << " * Now get \"" << nextString << "\" from the expression." << std::endl; }
        /* Get digit string: push into operands stack */
        if (isDigitString(nextString)) {
            char *temp;
            saveOperand(std::strtod(nextString.c_str(), &temp));
            continue;
        }
        /* Get an operator:
         * - First to deal with ')': calculate the expression in "()"
         * - Priority: last operator > this operator: pop and calculate last operator,
         *                                            and push `op` into operators stack
         * - First operator, or priority: this operator < last operator: only push `op` into operators stack  */
        char op = nextString[0];
        if (op == ')') {
            if (detail) { std::cout << " $ The sub expression in brackets will be calculated in advance." << std::endl; }
            while (!operators.empty() && operators.top() != '(') { calculateNext(); }
            getOperator(op);  // pop '('
            if (detail) { std::cout << " $ The calculation of sub expression finished." << std::endl; }
            continue;
        }
        if (!operators.empty() && operatorCompare(operators.top(), op) > 0) { calculateNext(); }
        saveOperator(op);
    }

    /* STEP3: Deal With the Remaining Operators. */
    if (detail) { std::cout << " * The expression reaches '#' or EOL." << std::endl; }
    while (!operators.empty()) { calculateNext(); }

    /* STEP4: Get the Result. */
    return getResult();
}

/**
 * Get one operator and do calculation.
 * @pre The conditions of stacks are suitable for next calculation.
 */
inline void InfixExpression::calculateNext() {
    char op;    // operator
    double left, right;   // operands
    getOperator(op);
    getOperands(left, right);
    saveOperand(digitCompute(left, op, right));
}

/**
 * Let left and right operand pop out of stack.
 * @post    Throw runtime_error if the operands stack is underflow.
 * @param left [out] left operand
 * @param right [out] right operand
 */
inline void InfixExpression::getOperands(double &left, double &right) {
    try {
        // Left and right operand pop out of stack
        right = operands.pop();
        if (detail) { std::cout << "|> Right operand " << right << " pop out of the operands stack." << std::endl; }
        left = operands.pop();
        if (detail) { std::cout << "|> Left operand " << left << " pop out of the operands stack." << std::endl; }
    } catch (std::underflow_error &) {  // except underflow error
        throw std::runtime_error{"[Popping operands] Invalid expression is given: missing operand(s)"};
    }
}

/**
 * Push result operand into operands stack.
 * @post    Throw runtime_error if the operands stack is overflow.
 * @param result [in] the operand that needs to push into the stack
 */
inline void InfixExpression::saveOperand(double result) {
    try {
        operands.push(result); // Result operand push into stack
        if (detail) { std::cout << "<| Push number " << result << " into the operands stack." << std::endl; }
    } catch (std::overflow_error &e) { // except overflow error
        throw std::runtime_error{std::string("[Pushing the operand] The expression too long, operands ") + e.what()};
    }
}

/**
 * Let top operator pop out of operator stack.
 * @post    Throw runtime_error if the operators stack is underflow.
 * @param op [out] next operator
 */
inline char &InfixExpression::getOperator(char &op) {
    try {
        op = operators.pop();
        if (detail) { std::cout << "|> Operator '" << op << "' pop out of operators stack." << std::endl; }
    } catch (std::underflow_error &) {
        throw std::runtime_error{"[Popping an operator] Invalid expression is given: missing operator(s)"};
    }
    return op;
}

/**
 * Let the operator push into operators stack.
 * @post    Check the validity of operator,
 *          throw runtime_error if the operands stack is overflow or operator is invalid.
 * @param op [in] operator that needs to push into the stack
 */
inline void InfixExpression::saveOperator(char op) {
    if (!(op == '+' || op == '~' || op == '*' || op == '/' || op == '(')) {
        // check the validity of operator
        throw std::runtime_error{"[Pushing the operator] Invalid operator is given"};
    }
    try {
        operators.push(op);
        if (detail) { std::cout << "<| Push operator '" << op << "' into operators stack." << std::endl; }
    } catch (std::overflow_error &e) {
        throw std::runtime_error{std::string("[Pushing the operator] The expression too long, operators ") + e.what()};
    }
}

/**
 * (CALLBACK function) Check the status when the calculation is complete and get the result.
 * @pre The calculation is finished, called when needs the result of expression.
 * @post Successful status: After pop the result in operands stack, both operands stack and operators stack is empty.
 * @return  the result of expression
 */
inline double /* CALLBACK */ InfixExpression::getResult() {
    double result;
    try {
        result = operands.pop();
    } catch (std::underflow_error &) {
        throw std::runtime_error{"[Getting result] Invalid expression is given: missing operand(s)"};
    }
    if (!operands.empty()) {
        if (detail) {
            std::cout << " * Failed to get the result! there are 2 or more elements in the operands stack: " << result;
            while (!operands.empty()) { std::cout << ", " << operands.pop(); }
            std::cout << std::endl;
        }
        throw std::runtime_error{"[Getting result] Invalid expression is given: missing operator(s)"};
    }
    if (detail) { std::cout << "|> Get the result " << result << " from the operands stack." << std::endl; }
    return result;
}

/**
 * Check the brackets match of the expression.
 * @post    Throw runtime_error contains the error information if brackets do not match.
 * @param expression [in] The infix expression.
 */
void InfixExpression::matchBracketCheck(const std::string &expression) {
    Stack<char> stack;
    for (char p : expression) {
        if (p == '(') {
            stack.push(p);
            continue;
        }
        if (p == ')' && (stack.empty() || stack.pop() != '(')) {  // not match, miss '('
            throw std::runtime_error{
                    "[Checking the bracket matching of the expression] "
                    "Invalid bracket matches of the expression: miss '('"
            };
        }
    }
    if (!stack.empty()) {   // not match, miss ')'
        throw std::runtime_error{
                "[Checking the bracket matching of the expression] "
                "Invalid bracket matches of the expression: miss ')'"
        };
    }
}

/**
 * Parse expressions for calculation.
 * @post     Check invalid characters, determine minus, and add blanks between operands and operators.
 * @param expression Original infix expression.
 * @return The expression after parsing.
 */
std::string InfixExpression::parseExpression(const std::string &expression) {
    std::string new_expression(expression);
    /* Step 1: Check invalid characters & Change '-' (means 'minus') to '~' ['-' means 'negative' keep still] */
    for (int i = 0; i < new_expression.length(); ++i) {
        if (!isValidChar(new_expression[i])) {
            throw std::runtime_error{"[Parsing the expression] Invalid expression is given: contain invalid character"};
        }
        determineMinus(new_expression, i);
    }
    /* Step 2: Add blanks between operands and operators to split them when calculate. */
    splitOperatorsOperands(new_expression);
    return new_expression;
}

/**
 * Compare operator precedence
 * @param old_op The operator already in stack
 * @param new_op New operator
 * @return bigger than 0 when old_op > new_op, less than 0 when old_op < new_op
 */
int InfixExpression::operatorCompare(char old_op, char new_op) noexcept {
    // priority to ')', and not push into operators stack
    switch (old_op) {
        case '(':   // already in stack, wait ')' to match
            return -1;
        case '*':   // only lower than '('; larger than others (include the same level)
        case '/':
            if (new_op == '(') return -1;
            return 1;
        case '+':   // only larger than the same level; lower than others (not include the same level)
        case '~':   // '~' means minus('-')
            if (new_op == '+' || new_op == '~') return 1;
            return -1;
    }
    exit(1);
}

/**
 * Do compute: `left op right`
 * @param left left operand
 * @param op operator
 * @param right right operand
 * @return the result
 */
double InfixExpression::digitCompute(double left, char op, double right) {
    // Do compute: `left op right`
    switch (op) {
        case '+':
            return left + right;
        case '~':
            return left - right;
        case '*':
            return left * right;
        case '/':
            if (right == 0) { throw std::runtime_error{"[When computing] Division by 0 error"}; }
            return left / right;
    }
    return 0.0;
}

/**
 * Determine whether the string is a float number
 * @param string
 * @return true if the string is a float number
 */
bool InfixExpression::isDigitString(const std::string &string) noexcept {
    // Determine whether the string is a number
    for (char ch : string) {
        if (!(ch == '-' || ch == '.' || std::isdigit(ch))) {
            return false;
        }
    }
    return true;
}

/**
 * Add blanks between operands and operators to split them when calculate.
 * @pre operands: '+', '~', '*', '/', '(', ')'
 * @param expression [in,out] The infix expression.
 */
void InfixExpression::splitOperatorsOperands(std::string &expression) noexcept {
    static const char ops[] = {'+', '~', '*', '/', '(', ')'};
    for (char op : ops) {
        std::string::size_type position = expression.find(op);  // find operator in loop
        while (position != std::string::npos) {
            expression = expression.replace(position, 1, {' ', op, ' '});  // add blank
            position = expression.find(op, position + 2);
        }
    }
}

/**
 * Check invalid characters.
 * @param ch unchecked character
 * @return true if valid, else false.
 */
bool InfixExpression::isValidChar(char ch) noexcept {
    static const std::string validString = "0123456789+-*/().";
    if (validString.find(ch) == std::string::npos) {
        return false;
    }
    return true;
}

/**
 * Change '-'(means 'minus') to '~' ['-' means 'negative' keep still]
 * @post    '-' means 'minus' when previous character is ')' or digit character,
 *          or next character is not digit character
 * @param expression [in,out] The infix expression.
 * @param pos The position of character '-' in the expression.
 */
void InfixExpression::determineMinus(std::string &expression, int pos) noexcept {
    if (pos != 0 && pos != expression.length() - 1 && expression[pos] == '-') {
        if (expression[pos - 1] == ')' || isdigit(expression[pos - 1]) || !isdigit(expression[pos + 1])) {
            // '-' means 'minus' when previous character is ')' or digit character, or next character is not digit character
            expression[pos] = '~';
        }
    }
    if (pos == 0 && expression[pos] == '-' && !isdigit(expression[pos + 1])) {   // next character isn't digit character
        expression[pos] = '~';
    }
    if (pos == expression.length() - 1 && expression[pos] == '-') {    // next character('\000') is not digit character
        expression[pos] = '~';
    }
}
