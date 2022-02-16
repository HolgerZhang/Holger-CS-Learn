//
// Created by Holger on 2021/9/6.
//

#include "regex.h"

/**
 * @brief Regex Constructor
 * @param str string
 */
lexer::Regex::Regex(std::string str)
    : origin(std::move(str)),
      intermediate_representation(convert_postfix(convert_infix(origin))) {}

/**
 * @brief Judge operator token
 */
bool lexer::Regex::is_operator(properties::TokenType token) {
  return std::any_of(properties::OPERATORS,
                     properties::OPERATORS + properties::OPERATOR_AMOUNT,
                     [&](properties::TokenType op) { return op == token; });
}

/**
 * @brief Convert string to infix-expression
 */
std::string lexer::Regex::convert_infix(std::string raw) {
  for (auto p = raw.begin() + 1; p < raw.end(); ++p) {
    if (*(p - 1) == properties::RIGHT_BRACKET ||
        *(p - 1) == properties::STAR_OPERATOR ||
        !is_operator(*(p - 1))) {
      if (*p == properties::LEFT_BRACKET || !is_operator(*p)) {
        p = raw.insert(p, properties::CAT_OPERATOR);
      }
    }
  }
  return raw;
}

/**
 * @brief Convert infix-expression to postfix-expression
 * @param infix infix-expression string
 * @return postfix-expression string
 */
std::string lexer::Regex::convert_postfix(const std::string &infix) {
  std::string postfix;
  std::stack<properties::TokenType> operators;
  std::size_t left_bracket_pos = 0;
  int left_bracket_count = 0;
  for (std::size_t i = 0; i < infix.length(); ++i) {
    // end tag
    if (i == infix.length() - 1) {
      if (infix[i] == properties::END_TAG) {
        continue;
      }
    }
    // search brackets, call this function recursively
    if (left_bracket_count != 0) {
      if (properties::LEFT_BRACKET == infix[i]) {
        left_bracket_count++;
      } else if (properties::RIGHT_BRACKET == infix[i]) {
        if (left_bracket_count <= 0) {
          throw std::runtime_error{"MISS_LEFT_BRACKET"};
        } else if (left_bracket_count == 1) {
          postfix.append(convert_postfix(
              infix.substr(left_bracket_pos + 1, i - left_bracket_pos - 1)));
          left_bracket_count--;
        } else {
          left_bracket_count--;
        }
      }
      continue;
    }
    // convert to postfix-expression
    if (properties::LEFT_BRACKET == infix[i]) {
      left_bracket_pos = i;
      left_bracket_count = 1;
    } else if (properties::RIGHT_BRACKET == infix[i]) {
      throw std::runtime_error{"MISS_LEFT_BRACKET"};
    } else if (is_operator(infix[i])) {
      if (operators.empty()) {
        operators.push(infix[i]);
      } else {
        properties::TokenType top = operators.top();
        if (properties::operator_priority(top)
            > properties::operator_priority(infix[i])) {
          postfix.append({top});
          operators.pop();
          operators.push(infix[i]);
        } else {
          operators.push(infix[i]);
        }
      }
    } else {
      postfix.append({infix[i]});
    }

  }
  // check left bracket all used
  if (left_bracket_count > 0) {
    throw std::runtime_error{"MISS_RIGHT_BRACKET"};
  }
  // left operators
  while (!operators.empty()) {
    postfix.append({operators.top()});
    operators.pop();
  }
  return postfix;
}

/**
 * @brief create NFA
 */
lexer::NFA lexer::Regex::parse() {
  std::stack<lexer::NFA> token_nfa{};
  for (auto token : this->intermediate_representation) {
    if (is_operator(token)) {
      switch (token) {
        case properties::CAT_OPERATOR:
          if (token_nfa.size() >= 2) {
            const NFA right = token_nfa.top();
            token_nfa.pop();
            NFA left = token_nfa.top();
            token_nfa.pop();
            token_nfa.push(left.myt_cat(right));
          } else {
            throw std::runtime_error{"REGEX_MISS_OPERAND"};
          }
          break;
        case properties::OR_OPERATOR:
          if (token_nfa.size() >= 2) {
            const NFA right = token_nfa.top();
            token_nfa.pop();
            NFA left = token_nfa.top();
            token_nfa.pop();
            token_nfa.push(left.myt_or(right));
          } else {
            throw std::runtime_error{"REGEX_MISS_OPERAND"};
          }
          break;
        case properties::STAR_OPERATOR:
          if (!token_nfa.empty()) {
            NFA operand = token_nfa.top();
            token_nfa.pop();
            token_nfa.push(operand.myt_star());
          } else {
            throw std::runtime_error{"REGEX_MISS_OPERAND"};
          }
          break;
        default:throw std::runtime_error{"REGEX_UNEXPECTED_OPERATOR"};
      }
    } else {
      token_nfa.emplace(token);
    }
  }
  State::amount = 0;
  if (token_nfa.size() != 1) {
    throw std::runtime_error{"REGEX_ERROR_FORMAT"};
  }
  return token_nfa.top();
}

