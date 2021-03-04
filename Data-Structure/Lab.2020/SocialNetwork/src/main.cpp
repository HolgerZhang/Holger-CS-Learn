#include <iostream>
#include "social_graph.h"
using namespace std;

int main() {
  SocialGraph graph;
  int n;
  cout << "\nShortest path Test\n";
  cout << "Number of tests:";
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int num1, num2;
    cout << "The id of person 1:";
    cin >> num1;
    cout << "The id of person 2:";
    cin >> num2;
    cout << "The shortest path between " << graph.get_name(num1) << " and "
         << graph.get_name(num2) << " is:"
         << graph.short_path(num1, num2) << endl;
  }
  cout << "\nPeople who may know Test\n";
  cout << "Number of tests:";
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int num;
    cout << "The id of person:";
    cin >> num;
    cout << "Person " << graph.get_name(num) << " may know: "
         << graph.people_may_know(num) << endl;
  }
  return 0;
}
