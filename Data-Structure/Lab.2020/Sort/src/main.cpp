// Project: Sort  File: main
// Created by holger on 2020/12/14.

#include <string>
#include <fstream>

#include "sorted_list.h"

using std::string;
using std::ofstream;

string resultName(const string &time_str, const string &desc) {
  string file("result-");
  file.append(time_str);
  file.append("-");
  file.append(desc);
  file.append(".txt");
  ofstream f(file);
  f.close();
  return file;
}

void test(SortedList::Type type, int size, const string &file) {
  SortedList L(type, size);
  SortedList::Information info{};
  int count = 5;
  double full_time = 0.0;
  for (int i = 0; i < count; ++i) {
    info = L.insertSort();
    L.showInformation("insert", info);
    full_time += info.time;
    L.reset();
  }
  info.time = full_time / count;
  L.recordInformation("insert", info, file);
  L.showInformation("--average--", info);

  full_time = 0.0;
  for (int i = 0; i < count; ++i) {
    info = L.bubbleSort();
    L.showInformation("bubble", info);
    full_time += info.time;
    L.reset();
  }
  info.time = full_time / count;
  L.recordInformation("bubble", info, file);
  L.showInformation("--average--", info);

  full_time = 0.0;
  for (int i = 0; i < count; ++i) {
    info = L.selectSort();
    L.showInformation("select", info);
    full_time += info.time;
    L.reset();
  }
  info.time = full_time / count;
  L.recordInformation("select", info, file);
  L.showInformation("--average--", info);

  full_time = 0.0;
  for (int i = 0; i < count; ++i) {
    info = L.shellSort();
    L.showInformation("shell", info);
    full_time += info.time;
    L.reset();
  }
  info.time = full_time / count;
  L.recordInformation("shell", info, file);
  L.showInformation("--average--", info);

  full_time = 0.0;
  for (int i = 0; i < count; ++i) {
    info = L.quickSort();
    L.showInformation("quick", info);
    full_time += info.time;
    L.reset();
  }
  info.time = full_time / count;
  L.recordInformation("quick", info, file);
  L.showInformation("--average--", info);

  full_time = 0.0;
  for (int i = 0; i < count; ++i) {
    info = L.heapSort();
    L.showInformation("heap", info);
    full_time += info.time;
    L.reset();
  }
  info.time = full_time / count;
  L.recordInformation("heap", info, file);
  L.showInformation("--average--", info);

  full_time = 0.0;
  for (int i = 0; i < count; ++i) {
    info = L.mergeSort();
    L.showInformation("merge", info);
    full_time += info.time;
    L.reset();
  }
  info.time = full_time / count;
  L.recordInformation("merge", info, file);
  L.showInformation("--average--", info);
}

int main() {
  string time_str = Timer::now();
  string files[] = {
      resultName(time_str, "random"),
      resultName(time_str, "positive"),
      resultName(time_str, "negative")
  };
  for (int i = 1; i <= 4; ++i) {
    test(SortedList::Type::random, 3 * (int) pow(10, i), files[0]);
    test(SortedList::Type::positive, 3 * (int) pow(10, i), files[1]);
    test(SortedList::Type::negative, 3 * (int) pow(10, i), files[2]);
  }
  return 0;
}
