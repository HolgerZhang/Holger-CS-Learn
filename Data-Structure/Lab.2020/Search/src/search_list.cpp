// Project: Search  File: search.cpp
// Created by holger on 2021/1/3.

#include "search_list.h"
const int SearchList::not_found = -1;

SearchList::SearchList(int size, bool unordered) : size_(size) {
  for (size_t i = 0; i < size; ++i) {
    data_[i] = 2 * i + 1;
  }
  if (unordered) {
    std::srand((unsigned) std::time(NULL));
    for (int i = 0; i < size; ++i) {
      std::swap(data_[std::rand() % size], data_[i]);
    }
  }
}

int SearchList::sequenceSearch(Record target, Information &info) {
  Time timer;
  for (int i = 0; i < size_; ++i) {
    if (info.compare++, target == data_[i]) {
      info.time = timer.runtime();
      return i;
    }
  }
  info.time = timer.runtime();
  return not_found;
}

int SearchList::binarySearch(Record target, Information &info) {
  Time timer;
  int res = binarySearchRecursive(0, size_ - 1, target, info);
  info.time = timer.runtime();
  return res;
}

int SearchList::binarySearchNonRecursive(Record target, Information &info) {
  Time timer;
  int mid, low = 0, high = size_ - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (info.compare++, target < data_[mid]) high = mid - 1;
    else if (info.compare++, target > data_[mid]) low = mid + 1;
    else {
      info.time = timer.runtime();
      return mid;
    }
  }
  info.time = timer.runtime();
  return not_found;
}

int SearchList::binarySearchRecursive(int low,
                                      int high,
                                      Record target,
                                      Information &info) {
  if (low > high) { return not_found; }
  int mid = (low + high) / 2;
  if (info.compare++, target < data_[mid]) {
    return binarySearchRecursive(low, mid - 1, target, info);
  } else if (info.compare++, target > data_[mid]) {
    return binarySearchRecursive(mid + 1, high, target, info);
  }
  return mid;
}

