#include <iostream>
#include <iomanip>
#include "search_list.h"

using namespace std;

int main() {
  cout << setiosflags(ios::fixed);
  int n, m;
  do {
    cout << "List size n = ";
    cin >> n;
  } while (n > MAX_SIZE);
    cout << "Search times m = ";
    cin >> m;
  SearchList ordered_list(n, false), unordered_list(n, true);

  // Sequence Search, unordered list, success
  Information sequence_unordered_success_info{};
  for (int i = 0; i < m; ++i) {
    Record record = 2 * int(i * n / m) + 1;
    Information info{};
    unordered_list.sequenceSearch(record, info);
    sequence_unordered_success_info.time += info.time;
    sequence_unordered_success_info.compare += info.compare;
  }
  sequence_unordered_success_info.time /= m;
  sequence_unordered_success_info.compare /= m;
  cout << "\nSequence Search, unordered list, success \n"
       << "time: " << sequence_unordered_success_info.time << endl
       << "compare: " << sequence_unordered_success_info.compare << endl;

  // Sequence Search, unordered list, fail
  Information sequence_unordered_fail_info{};
  for (int i = 0; i < m; ++i) {
    Record record = 2 * int(i * n / m);
    Information info{};
    unordered_list.sequenceSearch(record, info);
    sequence_unordered_fail_info.time += info.time;
    sequence_unordered_fail_info.compare += info.compare;
  }
  sequence_unordered_fail_info.time /= m;
  sequence_unordered_fail_info.compare /= m;
  cout << "\nSequence Search, unordered list, fail \n"
       << "time: " << sequence_unordered_fail_info.time << endl
       << "compare: " << sequence_unordered_fail_info.compare << endl;

  // Sequence Search, ordered list, success
  Information sequence_ordered_success_info{};
  for (int i = 0; i < m; ++i) {
    Record record = 2 * int(i * n / m) + 1;
    Information info{};
    ordered_list.sequenceSearch(record, info);
    sequence_ordered_success_info.time += info.time;
    sequence_ordered_success_info.compare += info.compare;
  }
  sequence_ordered_success_info.time /= m;
  sequence_ordered_success_info.compare /= m;
  cout << "\nSequence Search, ordered list, success \n"
       << "time: " << sequence_ordered_success_info.time << endl
       << "compare: " << sequence_ordered_success_info.compare << endl;

  // Sequence Search, ordered list, fail
  Information sequence_ordered_fail_info{};
  for (int i = 0; i < m; ++i) {
    Record record = 2 * int(i * n / m);
    Information info{};
    ordered_list.sequenceSearch(record, info);
    sequence_ordered_fail_info.time += info.time;
    sequence_ordered_fail_info.compare += info.compare;
  }
  sequence_ordered_fail_info.time /= m;
  sequence_ordered_fail_info.compare /= m;
  cout << "\nSequence Search, ordered list, fail \n"
       << "time: " << sequence_ordered_fail_info.time << endl
       << "compare: " << sequence_ordered_fail_info.compare << endl;

  // Binary Search, ordered list, success
  Information binary_ordered_success_info{};
  for (int i = 0; i < m; ++i) {
    Record record = 2 * int(i * n / m) + 1;
    Information info{};
    ordered_list.binarySearch(record, info);
    binary_ordered_success_info.time += info.time;
    binary_ordered_success_info.compare += info.compare;
  }
  binary_ordered_success_info.time /= m;
  binary_ordered_success_info.compare /= m;
  cout << "\nBinary Search, ordered list, success \n"
       << "time: " << binary_ordered_success_info.time << endl
       << "compare: " << binary_ordered_success_info.compare << endl;

  // Binary Search, ordered list, fail
  Information binary_ordered_fail_info{};
  for (int i = 0; i < m; ++i) {
    Record record = 2 * int(i * n / m);
    Information info{};
    ordered_list.binarySearch(record, info);
    binary_ordered_fail_info.time += info.time;
    binary_ordered_fail_info.compare += info.compare;
  }
  binary_ordered_fail_info.time /= m;
  binary_ordered_fail_info.compare /= m;
  cout << "\nBinary Search, ordered list, fail \n"
       << "time: " << binary_ordered_fail_info.time << endl
       << "compare: " << binary_ordered_fail_info.compare << endl;

  // Binary Search non-recursive, ordered list, success
  Information binary_n_ordered_success_info{};
  for (int i = 0; i < m; ++i) {
    Record record = 2 * int(i * n / m) + 1;
    Information info{};
    ordered_list.binarySearchNonRecursive(record, info);
    binary_n_ordered_success_info.time += info.time;
    binary_n_ordered_success_info.compare += info.compare;
  }
  binary_n_ordered_success_info.time /= m;
  binary_n_ordered_success_info.compare /= m;
  cout << "\nBinary Search non-recursive, ordered list, success \n"
       << "time: " << binary_n_ordered_success_info.time << endl
       << "compare: " << binary_n_ordered_success_info.compare << endl;

  // Binary Search non-recursive, ordered list, fail
  Information binary_n_ordered_fail_info{};
  for (int i = 0; i < m; ++i) {
    Record record = 2 * int(i * n / m);
    Information info{};
    ordered_list.binarySearchNonRecursive(record, info);
    binary_n_ordered_fail_info.time += info.time;
    binary_n_ordered_fail_info.compare += info.compare;
  }
  binary_n_ordered_fail_info.time /= m;
  binary_n_ordered_fail_info.compare /= m;
  cout << "\nBinary Search non-recursive, ordered list, fail \n"
       << "time: " << binary_n_ordered_fail_info.time << endl
       << "compare: " << binary_n_ordered_fail_info.compare << endl;

  return 0;
}
