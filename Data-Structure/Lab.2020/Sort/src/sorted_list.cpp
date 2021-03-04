// Project: src  File: SortedList
// Created by holger on 2020/12/14.

#include "sorted_list.h"

SortedList::SortedList(SortedList::Type type, int size) {
  length_ = size;
  data_ = nullptr;
  path_.assign("data/data_");
  switch (type) {
    case Type::random:type_.assign("random");
      break;
    case Type::positive:type_.assign("positive");
      break;
    case Type::negative:type_.assign("negative");
      break;
  }
  path_.append(type_);
  path_.append(std::to_string(size));
  path_.append(".data");
  reset();
}

SortedList::~SortedList() {
  delete[] data_;
}

void SortedList::reset() {
  std::ifstream dataStream(path_);
  if (!dataStream.is_open()) {
    std::cerr << path_ << " File Path Error." << std::endl;
    std::exit(0);
  }

  data_ = new int[length_]{};
  for (int i = 0; i < length_; ++i) {
    dataStream >> data_[i];
  }
  dataStream.close();
}

void SortedList::showInformation(const char *algorithmName,
                                 const SortedList::Information &cnt) {
  std::cout << algorithmName << ", type: " << type_ << ", size: " << length_
            << std::endl;
  std::cout << "using time  |\tcompare        |\tmoves          " << std::endl
            << std::setiosflags(std::ios::fixed | std::ios::left)
            << std::setprecision(6) << std::setw(12) << cnt.time << "|\t"
            << std::setw(15) << std::setiosflags(std::ios::left)
            << cnt.compare << "|\t"
            << std::setw(15) << std::setiosflags(std::ios::left)
            << cnt.move << std::endl;
}

SortedList::Information SortedList::insertSort() {
  Information information{};
  Timer timer;
  int i, j, temp;
  for (i = 1; i < length_; i++) {
    temp = data_[i];
    for (j = i - 1; j >= 0 && (information.compare++, temp < data_[j]); j--) {
      data_[j + 1] = data_[j], information.move++;
    }
    data_[j + 1] = temp;
  }
  information.time = timer.runtime();
  return information;
}

SortedList::Information SortedList::shellSort() {
  Information information{};
  Timer timer;
  int d, i, j, temp;
  for (d = length_ / 2; d >= 1; d = d / 2) {
    for (i = d; i < length_; i++) {
      temp = data_[i];
      for (j = i - d; j >= 0 && (information.compare++, temp < data_[j]);
           j = j - d) {
        data_[j + d] = data_[j], information.move++;
      }
      data_[j + d] = temp;
    }
  }
  information.time = timer.runtime();
  return information;
}

SortedList::Information SortedList::quickSort() {
  Information information{};
  Timer timer;
  recursiveQuickSort(0, length_ - 1, information);
  information.time = timer.runtime();
  return information;
}

void SortedList::recursiveQuickSort(int first,
                                    int last,
                                    SortedList::Information &information) {
  if (first >= last) { return; }
  int pivot = quickSortPartition(first, last, information);
  recursiveQuickSort(first, pivot - 1, information);  // quick sort left
  recursiveQuickSort(pivot + 1, last, information);  // quick sort right
}

int SortedList::quickSortPartition(int first,
                                   int last,
                                   SortedList::Information &information) {
  int i = first, j = last;
  while (i < j) {
    while (i < j && (information.compare++, data_[i] <= data_[j])) {
      j--; // right scan
    }
    if (i < j) {
      std::swap(data_[i], data_[j]), information.move++;
      i++;
    }
    while (i < j && (information.compare++, data_[i] <= data_[j])) {
      i++; // left scan
    }
    if (i < j) {
      std::swap(data_[i], data_[j]), information.move++;
      j--;
    }
  }
  return i;
}

SortedList::Information SortedList::selectSort() {
  Information information{};
  Timer timer;
  int i, j, index;
  for (i = 0; i < length_ - 1; i++) {
    index = i;
    for (j = i + 1; j < length_; j++) {
      if (information.compare++, data_[j] < data_[index]) { //min record
        index = j;
      }
    }
    if (index != i) {
      std::swap(data_[i], data_[index]), information.move++;
    }
  }
  information.time = timer.runtime();
  return information;
}

SortedList::Information SortedList::heapSort() {
  Information information{};
  Timer timer;
  int i;
  for (i = (int) std::ceil(length_ / 2) - 1; i >= 0; i--) {
    // last node to root node
    heapSift(i, length_ - 1, information);
  }
  for (i = 1; i < length_; i++) {
    std::swap(data_[0], data_[length_ - i]), information.move++;
    heapSift(0, length_ - i - 1, information); // rebuilt heap
  }
  information.time = timer.runtime();
  return information;
}

void SortedList::heapSift(int k,
                          int last,
                          SortedList::Information &information) {
  int i, j;
  i = k;
  j = 2 * i + 1; // j = i->left
  while (j <= last) {
    if (j < last && (information.compare++, data_[j] < data_[j + 1]))
      j++; // j -> max
    if (information.compare++, data_[i] > data_[j]) {
      break; //heap
    } else {
      std::swap(data_[i], data_[j]), information.move++;
      i = j;
      j = 2 * i + 1;
    }
  }
}

SortedList::Information SortedList::mergeSort() {
  Information information{};
  Timer timer;
  recursiveMergeSort(0, length_ - 1, information);
  information.time = timer.runtime();
  return information;
}

void SortedList::recursiveMergeSort(int first,
                                    int last,
                                    SortedList::Information &information) {
  if (first >= last) { return; }
  int mid = (first + last) / 2;
  recursiveMergeSort(first, mid, information); // merge sort left
  recursiveMergeSort(mid + 1, last, information); // merge sort right
  merge(first, mid, last, information); // merge
}

void SortedList::merge(int first1,
                       int last1,
                       int last2,
                       SortedList::Information &information) {
  int *temp = new int[length_];
  int i = first1, j = last1 + 1, k = first1;
  while (i <= last1 && j <= last2) {
    if (information.compare++, data_[i] <= data_[j]) {
      temp[k++] = data_[i++]; // min -> temp[k]
    } else {
      temp[k++] = data_[j++];
    }
    information.move++;
  }
  while (i <= last1) { // subSequence1
    temp[k++] = data_[i++];
    information.move++;
  }
  while (j <= last2) { // subSequence2
    temp[k++] = data_[j++];
    information.move++;
  }
  for (i = first1; i <= last2; i++) {
    data_[i] = temp[i];
  }
  delete[] temp;
}

SortedList::Information SortedList::bubbleSort() {
  Information information{};
  Timer timer;
  int j, exchange, bound;
  exchange = length_ - 1;
  while (exchange != 0) {
    bound = exchange;
    exchange = 0;
    for (j = 0; j < bound; j++) {
      if (information.compare++, data_[j] > data_[j + 1]) {
        std::swap(data_[j], data_[j + 1]), information.move++;
        exchange = j;
      }
    }
  }
  information.time = timer.runtime();
  return information;
}

void SortedList::recordInformation(const char *algorithmName,
                                   const SortedList::Information &information,
                                   const std::string &record) {
  std::ofstream append(record, std::ios::app);
  append << algorithmName << '\t' << type_ << '\t' << length_ << '\t'
         << std::setiosflags(std::ios::fixed) << std::setprecision(6)
         << information.time << '\t' << information.compare << '\t'
         << information.move << std::endl;
  append.close();
}

