//
// Created by Holger on 2021/9/15.
//

#include "nfa.h"
#include "dfa_helper.hpp"

lexer::NFA::NFA(properties::TokenType token) {
  start_state = State();
  accept_states.emplace_back();
  edges.emplace_back(start_state, token, accept_states.front());
}

/**
 * @brief create cat-node
 * @param other right operand
 * @return cat(this, other)
 */
lexer::NFA &lexer::NFA::myt_cat(const lexer::NFA &other) {
  NFA another(other);
  for (auto &edge : another.edges) {
    if (edge.from.tag == another.start_state.tag) {
      edge.from = this->accept_states.front();
    } else if (edge.from.tag > another.start_state.tag) {
      edge.from.tag--;
    }
    if (edge.to.tag > another.start_state.tag) {
      edge.to.tag--;
    }
    this->edges.push_back(edge);
  }
  this->accept_states.clear();
  for (auto &state : another.accept_states) {
    if (state.tag > another.start_state.tag) {
      state.tag--;
    }
    this->accept_states.push_back(state);
  }
  return *this;
}

/**
 * @brief create star-node
 * @return star(this)
 */
lexer::NFA &lexer::NFA::myt_star() {
  edges.emplace_back(accept_states.front(),
                     properties::EMPTY_TOKEN,
                     start_state);
  State new_start;
  edges.emplace_front(new_start, properties::EMPTY_TOKEN, start_state);
  start_state = new_start;
  State new_accept;
  edges.emplace_back(accept_states.front(),
                     properties::EMPTY_TOKEN,
                     new_accept);
  edges.emplace_front(new_start, properties::EMPTY_TOKEN, new_accept);
  accept_states.clear();
  accept_states.push_back(new_accept);
  return *this;
}

/**
 * @brief create or-node
 * @param other right operand
 * @return or(this, other)
*/
lexer::NFA &lexer::NFA::myt_or(const lexer::NFA &other) {
  State new_start;
  edges.emplace_front(new_start, properties::EMPTY_TOKEN, this->start_state);
  edges.emplace_front(new_start, properties::EMPTY_TOKEN, other.start_state);
  this->start_state = new_start;
  for (auto edge : other.edges) {
    this->edges.push_back(edge);
  }
  State new_accept;
  edges.emplace_back(this->accept_states.front(),
                     properties::EMPTY_TOKEN,
                     new_accept);
  edges.emplace_back(other.accept_states.front(),
                     properties::EMPTY_TOKEN,
                     new_accept);
  accept_states.clear();
  accept_states.push_back(new_accept);
  return *this;
}

/**
 * @brief subset construction
 * @return DFA
 */
lexer::DFA lexer::NFA::subset_construction() {
  State::amount = 0;
  std::vector<dfa_helper::DFA_State> DStates;
  dfa_helper::DFA_State dfa_start{e_closure(start_state), State()};
  DStates.push_back(dfa_start);
  std::list<Edge> DTran;
  int t_pos;
  while ((t_pos = get_unmasked(DStates)) != -1) {
    DStates[t_pos].flag = true;
    for (auto token : this->tokens()) {
      auto u = e_closure_t(move(DStates[t_pos].states, token));
      State to(-1);
      if (!contains(DStates, u)) {
        to = State();
        DStates.emplace_back(u, to);
      } else {
        to = std::find_if(DStates.begin(),
                          DStates.end(),
                          [&](const dfa_helper::DFA_State &s) {
                            return s.states == u;
                          })->real;
      }
      DTran.emplace_back(DStates[t_pos].real, token, to);
    }
  }
  lexer::DFA dfa;
  dfa.start_state = dfa_start.real;
  dfa.edges.assign(DTran.begin(), DTran.end());
  for (const auto &ds : DStates) {
    if (is_DFA_accept_state(ds, this->accept_states)) {
      dfa.accept_states.push_back(ds.real);
    }
  }
  State::amount = 0;
  return dfa;
}

/**
 * @brief e-closure for state
 */
lexer::FA::StateList lexer::NFA::e_closure(const lexer::State &state) {
  std::stack<lexer::State> st;
  st.push(state);
  lexer::FA::StateList closure;
  closure.push_back(state);
  while (!st.empty()) {
    auto top = st.top();
    st.pop();
    for (auto edge : this->edges) {
      if (edge.token == properties::EMPTY_TOKEN && edge.from.tag == top.tag
          && !dfa_helper::contains(closure, edge.to)) {
        closure.push_back(edge.to);
        st.push(edge.to);
      }
    }
  }
  return closure;
}

/**
 * @brief e-closure for the set of states
 */
lexer::FA::StateList lexer::NFA::e_closure_t(const lexer::FA::StateList &state_list) {
  std::stack<lexer::State> st;
  for (auto &state : state_list) {
    st.push(state);
  }
  lexer::FA::StateList closure(state_list);
  while (!st.empty()) {
    auto top = st.top();
    st.pop();
    for (auto u : e_closure(top)) {
      if (!dfa_helper::contains(closure, u)) {
        closure.push_back(u);
        st.push(u);
      }
    }
  }
  return closure;
}

/**
 * @brief move action
 */
lexer::FA::StateList lexer::NFA::move(const lexer::FA::StateList &state_list,
                                      properties::TokenType a) {
  lexer::FA::StateList ans;
  for (auto s : state_list) {
    for (auto edge : this->edges) {
      if (a == edge.token && edge.from.tag == s.tag
          && !dfa_helper::contains(ans, edge.to)) {
        ans.push_back(edge.to);
      }
    }
  }
  return ans;
}