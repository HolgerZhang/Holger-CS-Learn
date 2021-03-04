// Project: Sort_DS  File: main.cpp
// Created by holger on 2021/1/3.

#include <iostream>
#include <algorithm>
const int MAX = 10005;
using namespace std;

struct Hotel {
  int d, c;
  bool operator<(const Hotel &hotel) const {
    if (c == hotel.c) return d < hotel.d;
    return c < hotel.c;
  }
} hotels[MAX];

int main() {
  int n;
  while (cin >> n && n != 0) {
    for (int i = 0; i < n; ++i) {
      cin >> hotels[i].d >> hotels[i].c;
    }
    sort(hotels, hotels + n);
    int ans = 0, min_d = MAX;
    for (int i = 0; i < n; ++i) {
      if (hotels[i].d < min_d) {
        ans++;
        min_d = hotels[i].d;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
