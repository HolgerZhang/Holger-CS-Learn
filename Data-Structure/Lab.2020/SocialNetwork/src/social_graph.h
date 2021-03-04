// Project: SocialNetwork  File: social_graph.h
// Created by holger on 2021/1/3.

#include <iostream>
#include <sstream>
#include <string>

#ifndef SOCIALNETWORK__SOCIAL_GRAPH_H_
#define SOCIALNETWORK__SOCIAL_GRAPH_H_

#define MaxSize 100
#define INF     0x3f3f3f
/**
 * SocialGraph Class
 */
class SocialGraph {
 public:
  SocialGraph();
  SocialGraph(const SocialGraph &) = delete;
  ~SocialGraph() = default;
  std::string get_name(int i) const ;
  std::string short_path(int source, int destination);
  std::string people_may_know(int people);
 private:
  std::string vertex_[MaxSize];
  int edge_[MaxSize][MaxSize]{};
  int vertex_num_{};
  static int min(const int r[], int n);
};

#endif //SOCIALNETWORK__SOCIAL_GRAPH_H_
