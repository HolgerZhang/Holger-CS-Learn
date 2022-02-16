//
// Created by Holger on 2021/9/6.
//

#include <set>
#include <map>
#include <list>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "properties.h"

#ifndef LEXER__FINITE_STATE_MACHINE_H_
#define LEXER__FINITE_STATE_MACHINE_H_

namespace lexer {

/**
 * @brief FA State
 */
struct State {
  int tag{};
  static int amount;
  State() {
    tag = amount;
    amount++;
  }
  explicit State(int tag) : tag(tag) {}
  bool operator==(const State &o) const {
    return this->tag == o.tag;
  }
  bool operator<(const State &o) const {
    return this->tag < o.tag;
  }
};

/**
 * @brief Graph Edge
 */
struct Edge {
  Edge(State from, properties::TokenType token, State to);
  State from{};
  properties::TokenType token{};
  State to{};
};

/**
 * @brief Finite State Machine (or Finite Automata Machine), for NFA and DFA
 */
class FA {
 public:
  FA() = default;
  virtual std::string to_string() const;
  using StateSet = std::set<lexer::State>;
  using StateList = std::vector<lexer::State>;

 protected:
  std::list<State> accept_states{};
  void create(const std::vector<std::string> &data);
  State start_state{-1};
  std::list<Edge> edges{};
  std::set<properties::TokenType> tokens();
  StateSet total_states();
};

inline std::ostream &operator<<(std::ostream &os, const FA &m) {
  return os << m.to_string();
}

}

#endif //LEXER__FINITE_STATE_MACHINE_H_
