// Project: src  File: SortedList
// Created by holger on 2020/12/14.

#ifndef SORT_SORTED_LIST_H_
#define SORT_SORTED_LIST_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "timer.hpp"

/**
 * SortedList Class
 */
class SortedList {
 public:
  enum class Type {
    random, positive, negative
  };

  struct Information {
    long long compare;
    long long move;
    double time;
  };

  SortedList(Type type, int size);

  virtual ~SortedList();

  void reset();

  void showInformation(const char *algorithmName,
                       const Information &information);

  void recordInformation(const char *algorithmName,
                         const Information &information,
                         const std::string &record);

  Information insertSort();

  Information shellSort();

  Information quickSort();

  Information selectSort();

  Information heapSort();

  Information mergeSort();

  Information bubbleSort();

 private:
  int *data_{};
  int length_{};
  std::string path_{};
  std::string type_{};

  int quickSortPartition(int first, int last, Information &information);

  void recursiveQuickSort(int first, int last, Information &information);

  void heapSift(int k, int last, Information &information);

  void recursiveMergeSort(int first, int last, Information &information);

  void merge(int first1, int last1, int last2, Information &information);
};

#endif //SORT_SORTED_LIST_H_
