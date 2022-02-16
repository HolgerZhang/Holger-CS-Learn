//
// Created by Holger on 2021/9/15.
//

#include "dfa.h"
#include "dfa_helper.hpp"

/**
 * @brief DFA minimize
 * @return Minimum DFA
 */
lexer::DFA lexer::DFA::minimize() {
  auto partition_states = this->hopcroft();
  std::vector<State> real_states;
  DFA dfa;
  State::amount = 0;
  for (std::size_t i = 0; i < partition_states.size(); ++i) {
    real_states.emplace_back();
  }
  // start state
  for (std::size_t i = 0; i < partition_states.size(); ++i) {
    if (dfa_helper::contains(partition_states[i], start_state)) {
      dfa.start_state = real_states[i];
      break;
    }
  }
  // accept states
  for (std::size_t i = 0; i < partition_states.size(); ++i) {
    for (auto accept : accept_states) {
      if (dfa_helper::contains(partition_states[i], accept)) {
        dfa.accept_states.push_back(real_states[i]);
        break;
      }
    }
  }
  // edges
  for (std::size_t i = 0; i < partition_states.size(); ++i) {
    for (auto raw_state : partition_states[i]) {
      for (auto edge : this->edges) {
        if (edge.from.tag == raw_state.tag) {
          for (std::size_t j = 0; j < partition_states.size(); ++j) {
            if (dfa_helper::contains(partition_states[j], edge.to)) {
              dfa_helper::insert_edge_if_not_exists(
                  dfa.edges, {real_states[i], edge.token, real_states[j]});
            }
          }
        }
      }
    }
  }
  State::amount = 0;
  return dfa;
}

/**
 * @brief hopcroft algorithm
 * @see https://www.omegaxyz.com/2019/02/01/hopcroft-min-dfa/
 * @return state partition
 */
std::vector<lexer::FA::StateSet> lexer::DFA::hopcroft() {
  std::set<properties::TokenType> tokens = this->tokens();
  lexer::FA::StateSet termination_states;
  for (auto s : this->accept_states) {
    termination_states.insert(s);
  }
  lexer::FA::StateSet total_states = this->total_states();
  lexer::DFA::TranMap state_transition_map = this->state_transition_map();
  lexer::FA::StateSet not_termination_states;
  // not_termination_states = total_states - termination_states
  std::set_difference(total_states.begin(),
                      total_states.end(),
                      termination_states.begin(),
                      termination_states.end(),
                      std::inserter(not_termination_states,
                                    not_termination_states.begin()));
  std::vector<lexer::FA::StateSet>
      p{termination_states, not_termination_states};
  std::list<lexer::FA::StateSet>
      w{termination_states, not_termination_states};
  while (!w.empty()) {
    auto a = w.front();
    w.erase(w.begin());  // remove w front
    for (auto ch : tokens) {
      auto x = dfa_helper::get_source_set(a, ch, total_states,
                                          state_transition_map);
      std::vector<lexer::FA::StateSet> p_temp;
      for (const auto &y : p) {
        lexer::FA::StateSet s, s1;
        std::set_intersection(x.begin(), x.end(),
                              y.begin(), y.end(),
                              std::inserter(s, s.begin()));  // s = x & y
        std::set_difference(y.begin(), y.end(), x.begin(), x.end(),
                            std::inserter(s1, s1.begin()));  // s1 = y - x
        if (!s.empty() && !s1.empty()) {
          p_temp.push_back(s);
          p_temp.push_back(s1);
          if (dfa_helper::remove_item_if_exists(y, w)) {
            w.push_back(s);
            w.push_back(s1);
          } else {
            if (s.size() <= s1.size()) {
              w.push_back(s);
            } else {
              w.push_back(s1);
            }
          }
        } else {
          p_temp.push_back(y);
        }
      }
      p.clear();
      p.assign(p_temp.begin(), p_temp.end());
    }
  }
  return p;
}

/**
 * @brief State transition table
 */
lexer::DFA::TranMap lexer::DFA::state_transition_map() {
  lexer::DFA::TranMap map;
  for (auto state : this->total_states()) {
    map[state] = std::map<properties::TokenType, lexer::State>();
  }
  for (auto edge : this->edges) {
    map[edge.from][edge.token] = edge.to;
  }
  return map;
}

