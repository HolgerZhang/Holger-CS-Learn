//
// Created by holger on 2020/10/4.
//
#include <iostream>
#include "set.hpp"

void printI(int &i) { std::cout << i << ' '; }

int main() {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int b[5] = {11, 22, 33, 4, 5};
    Set<int> set1(a, 10), set2(b, 5);
    Set<int> union_set(set1.set_union(set2)), intersection_set(set1.set_intersection(set2)),
            dif12(set1.set_difference(set2)), dif21(set2.set_difference(set1));
    set1.traverse(printI);
    std::cout << std::endl;
    set2.traverse(printI);
    std::cout << std::endl;
    union_set.traverse(printI);
    std::cout << std::endl;
    intersection_set.traverse(printI);
    std::cout << std::endl;
    dif12.traverse(printI);
    std::cout << std::endl;
    dif21.traverse(printI);
    std::cout << std::endl;
    std::cout << (union_set.is_superset(set1) ? "yes" : "no") << std::endl; // yes
    std::cout << (union_set.is_subset(set2) ? "yes" : "no") << std::endl; // no
    std::cout << (intersection_set.is_superset(set1) ? "yes" : "no") << std::endl; // no
    std::cout << (intersection_set.is_subset(set2) ? "yes" : "no") << std::endl; // yes
    std::cout << (dif12.is_subset(set1) ? "yes" : "no") << std::endl; // yes
    std::cout << (dif21.is_subset(set1) ? "yes" : "no") << std::endl; // no
    return 0;
}