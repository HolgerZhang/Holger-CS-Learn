// Project:SocialNetwork  File:social_graph.cpp
// Created by holger on 2021/1/3.

#include "social_graph.h"

SocialGraph::SocialGraph() {
  std::memset(edge_, INF, sizeof(int) * MaxSize * MaxSize);
  std::cout << "The number of people:";
  std::cin >> vertex_num_;
  if (vertex_num_ > MaxSize) {
    std::cout << "Size Overflow\n";
    exit(1);
  }
  std::cout << "The name of people:";
  for (int i = 0; i < vertex_num_; ++i) {
    std::cin >> vertex_[i];
  }
  std::cout << "People's id is numbered from 0 to " << vertex_num_ - 1 << ".\n";
  for (int i = 0; i < vertex_num_; ++i) {
    int n, f;
    std::cout << "The number of " << vertex_[i] << "'s friends:";
    std::cin >> n;
    std::cout << vertex_[i] << "'s friends are (use id):";
    for (int j = 0; j < n; ++j) {
      std::cin >> f;
      if (f >= vertex_num_ && f < 0) {
        std::cout << "out of range";
        exit(2);
      }
      edge_[i][f] = 1;
      edge_[f][i] = 1;
    }
  }
}

std::string SocialGraph::short_path(int source, int destination) {
  if ((source >= vertex_num_ || source < 0)
      || (destination >= vertex_num_ || destination < 0)) {
    std::cerr << "out of range" << std::endl;
    exit(3);
  }
  int i, k, num, dist[MaxSize];
  std::string path[MaxSize];
  for (i = 0; i < vertex_num_; i++) {
    dist[i] = edge_[source][i];
    if (dist[i] == 1) {
      path[i] = vertex_[source] + " > " + vertex_[i];
    } else { path[i] = ""; }
  }
  for (num = 1; num < vertex_num_; num++) {
    k = min(dist, vertex_num_);
    for (i = 0; i < vertex_num_; i++)
      if (dist[i] > dist[k] + edge_[k][i]) {
        dist[i] = dist[k] + edge_[k][i];
        path[i] = path[k] + " > " + vertex_[i];
      }
    dist[k] = 0;
  }
  return path[destination];
}

int SocialGraph::min(const int r[], int n) {
  int index = 0, min_num = MaxSize;
  for (int i = 0; i < n; i++)
    if (r[i] != 0 && r[i] < min_num) {
      min_num = r[i];
      index = i;
    }
  return index;
}
std::string SocialGraph::people_may_know(int people) {
  if (people >= vertex_num_ || people < 0) {
    std::cerr << "out of range" << std::endl;
    exit(3);
  }
  int edge_2[MaxSize][MaxSize]{};
  for (int i = 0; i < vertex_num_; i++) {
    for (int j = 0; j < vertex_num_; j++) {
      for (int k = 0; k <= vertex_num_; k++) {
        int x = 0, y = 0;
        if (edge_[i][k] == 1) { x = 1; }
        if (edge_[k][j] == 1) { y = 1; }
        edge_2[i][j] += x * y;
      }
    }
  }
  std::ostringstream out;
  for (int i = 0; i < vertex_num_; ++i) {
    if (people != i && edge_2[people][i] >= 1 && edge_[people][i] != 1) {
      out << vertex_[i] << ' ';
    }
  }
  return out.str();
}

std::string SocialGraph::get_name(int i) const {
  if (i >= vertex_num_ || i < 0) {
    std::cerr << "out of range" << std::endl;
    exit(3);
  }
  return vertex_[i];
}
