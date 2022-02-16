//
// Created by Holger on 2021/9/6.
// Properties definitions
//

#include <stdexcept>

#ifndef LEXER__PROPERTIES_H_
#define LEXER__PROPERTIES_H_

namespace properties {
using TokenType = char;

const TokenType OR_OPERATOR = '|';
const TokenType CAT_OPERATOR = '+';
const TokenType STAR_OPERATOR = '*';
const TokenType LEFT_BRACKET = '(';
const TokenType RIGHT_BRACKET = ')';
const TokenType END_TAG = '#';

const TokenType OPERATORS[]{
    OR_OPERATOR,
    CAT_OPERATOR,
    STAR_OPERATOR,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    END_TAG
};

const TokenType EMPTY_TOKEN = 'e';
const char SPLIT_CHAR = ' ';

const int OPERATOR_AMOUNT = 6;

inline static int operator_priority(const TokenType &token) {
  switch (token) {
    case OR_OPERATOR:return 1;
    case CAT_OPERATOR:return 2;
    case STAR_OPERATOR:return 3;
    default:throw std::runtime_error{"ERROR_IR_FORMAT"};
  }
}
}

#endif //LEXER__PROPERTIES_H_
