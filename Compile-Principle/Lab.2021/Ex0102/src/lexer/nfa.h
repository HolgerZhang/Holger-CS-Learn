//
// Created by Holger on 2021/9/15.
//

#include "fa.h"
#include "dfa.h"

#ifndef LEXER_HOLGER_LEXER_NFA_H_
#define LEXER_HOLGER_LEXER_NFA_H_

namespace lexer {

/**
 * @brief NFA, constructed by Regex
 */
class NFA : public lexer::FA {
 public:
  explicit NFA(properties::TokenType token);
  explicit NFA(const std::vector<std::string> &data) { this->create(data); }
  NFA &myt_cat(const NFA &other);
  NFA &myt_star();
  NFA &myt_or(const NFA &other);
  DFA subset_construction();
 private:
  StateList e_closure(const lexer::State &state);
  StateList e_closure_t(const StateList &state_list);
  StateList move(const StateList &state_list, properties::TokenType a);
};

}

#endif //LEXER_HOLGER_LEXER_NFA_H_
