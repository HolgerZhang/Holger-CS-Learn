//
// Created by Holger on 2021/9/14.
//

#include "dfa.h"

#ifndef LEXER_HOLGER_LEXER_DFA_HELPER_H_
#define LEXER_HOLGER_LEXER_DFA_HELPER_H_

#define NOTHING_TO_DO  do {} while(0)

namespace lexer {
namespace dfa_helper {

inline std::vector<std::string> split(const std::string &str, char ch) {
  std::istringstream iss(str);
  std::vector<std::string> result;
  std::string buffer;
  while (std::getline(iss, buffer, ch)) {
    if (buffer.length() > 0) {
      result.push_back(buffer);
    }
  }
  return result;
}

inline bool contains(const lexer::FA::StateList &lst,
                     const lexer::State &item) {
  return std::any_of(lst.begin(),
                     lst.end(),
                     [&](const lexer::State &i) { return i.tag == item.tag; });
}

inline bool contains(const lexer::FA::StateSet &lst,
                     const lexer::State &item) {
  return std::any_of(lst.begin(),
                     lst.end(),
                     [&](const lexer::State &i) { return i.tag == item.tag; });
}

struct DFA_State {
  lexer::FA::StateList states{};
  lexer::State real{-1};
  bool flag = false;
  DFA_State(std::vector<State> t, State state)
      : states(std::move(t)), real(state), flag(false) {}
};

inline bool contains(const std::vector<DFA_State> &lst,
                     const lexer::FA::StateList &item) {
  return std::any_of(lst.begin(),
                     lst.end(),
                     [&](const DFA_State &i) { return i.states == item; });
}

inline int get_unmasked(std::vector<DFA_State> &DStates) {
  for (int i = 0; i < DStates.size(); ++i) {
    if (!DStates[i].flag) {
      return i;
    }
  }
  return -1;
}

inline bool is_DFA_accept_state(const DFA_State &dfa_state,
                                const std::list<lexer::State> &nfa_accepts) {
  for (auto i : dfa_state.states) {
    for (auto j : nfa_accepts) {
      if (i.tag == j.tag) {
        return true;
      }
    }
  }
  return false;
}

inline bool remove_item_if_exists(const lexer::FA::StateSet &y,
                                  std::list<lexer::FA::StateSet> &w) {
  for (const auto &p : w) {
    if (p == y) {
      w.remove(y);
      return true;
    }
  }
  return false;
}

inline void insert_edge_if_not_exists(std::list<Edge> &edges,
                                      const Edge &edge) {
  if (std::find_if(edges.begin(), edges.end(), [&](Edge &e) {
    return e.token == edge.token && e.from == edge.from && e.to == edge.to;
  }) == edges.end()) {
    edges.push_back(edge);
  }
}

inline lexer::FA::StateSet get_source_set(const FA::StateSet &target_set,
                                          properties::TokenType ch,
                                          const FA::StateSet &total_states,
                                          const DFA::TranMap &state_transition_map) {
  FA::StateSet source_set;
  for (const auto &state : total_states) {
    try {
      if (dfa_helper::contains(target_set,
                               state_transition_map.at(state).at(ch))) {
        source_set.insert(state);
      }
    } catch (const std::out_of_range &) {
      NOTHING_TO_DO;
    }
  }
  return source_set;
}

}
}

#endif //LEXER_HOLGER_LEXER_DFA_HELPER_H_
