//
// Created by Holger on 2021/9/6.
//

#include "fa.h"
#include "dfa_helper.hpp"

int lexer::State::amount = 0;

lexer::Edge::Edge(lexer::State from,
                  properties::TokenType token,
                  lexer::State to) : from(from), token(token), to(to) {}

std::string lexer::FA::to_string() const {
  std::ostringstream oss;
  for (auto edge : edges) {
    oss << edge.from.tag << properties::SPLIT_CHAR << edge.token
        << properties::SPLIT_CHAR << edge.to.tag
        << std::endl;
  }
  oss << "start state:" << properties::SPLIT_CHAR << start_state.tag
      << std::endl;
  oss << "accepting states:";
  for (auto state : accept_states) {
    oss << properties::SPLIT_CHAR << state.tag;
  }
  oss << std::endl;
  return oss.str();
}

/**
 * @brief create FA by string data
 * @param data list of string
 */
void lexer::FA::create(const std::vector<std::string> &data) {
  this->accept_states.clear();
  this->edges.clear();
  // edge
  for (std::size_t i = 0; i < data.size() - 2; ++i) {
    auto edge_item = dfa_helper::split(data[i], properties::SPLIT_CHAR);
    this->edges.emplace_back(State(std::stoi(edge_item[0])),
                             edge_item[1].front(),
                             State(std::stoi(edge_item[2])));
  }
  // start state
  auto start_item = dfa_helper::split(data[data.size() - 2],
                                      properties::SPLIT_CHAR);
  this->start_state = State(std::stoi(start_item[start_item.size() - 1]));
  // accept states
  auto accept_item = dfa_helper::split(data[data.size() - 1],
                                       properties::SPLIT_CHAR);
  for (auto s : accept_item) {
    if (isdigit(s.front())) {
      this->accept_states.emplace_back(std::stoi(s));
    }
  }
}

/**
 * @brief get input alphabet
 */
std::set<properties::TokenType> lexer::FA::tokens() {
  std::set<properties::TokenType> t_s;
  for (auto edge : this->edges) {
    if (edge.token != properties::EMPTY_TOKEN) {
      t_s.insert(edge.token);
    }
  }
  return t_s;
}

/**
 * @brief get all states
 */
lexer::FA::StateSet lexer::FA::total_states() {
  lexer::FA::StateSet states;
  for (auto edge : edges) {
    states.insert(edge.from);
    states.insert(edge.to);
  }
  return states;
}
