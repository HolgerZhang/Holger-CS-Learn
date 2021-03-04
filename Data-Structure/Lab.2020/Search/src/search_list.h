// Project: Search  File: search_list.h
// Created by holger on 2021/1/3.

#include <fstream>
#include <vector>
#include <ctime>
#include "timer.hpp"

#ifndef SEARCH__SEARCH_H_
#define SEARCH__SEARCH_H_

#define MAX_SIZE  1000000
using Record = int;

struct Information {
  double time;
  unsigned long long compare;
};

class SearchList {
 public:
  SearchList() = default;
  explicit SearchList(int size, bool unordered = false);
  static const int not_found;
  int sequenceSearch(Record target, Information &info);
  int binarySearch(Record target, Information &info);
  int binarySearchNonRecursive(Record target, Information &info);
 private:
  int data_[MAX_SIZE]{};
  int size_{};
  int binarySearchRecursive(int low,
                            int high,
                            Record target,
                            Information &info);
};

#endif //SEARCH__SEARCH_H_
