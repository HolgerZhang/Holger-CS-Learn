//
// Created by Holger on 2021/9/6.
//

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include "properties.h"
#include "nfa.h"

#ifndef LEXER__REGEX_H_
#define LEXER__REGEX_H_

namespace lexer {

/**
 * @brief regular expression
 */
class Regex {
 public:
  explicit Regex(std::string str);
  lexer::NFA parse();
  inline std::string get_ir() const { return intermediate_representation; }
  static bool is_operator(properties::TokenType);

 private:
  const std::string origin;
  std::string intermediate_representation;
  static std::string convert_infix(std::string raw);
  static std::string convert_postfix(const std::string &infix);
};

}

#endif //LEXER__REGEX_H_
