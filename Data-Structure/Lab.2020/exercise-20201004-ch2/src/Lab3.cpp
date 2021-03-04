//
// Created by holger on 2020/10/4.
//
#include <iostream>
#include "warehouse.h"

int main() {
    Warehouse warehouse;
    warehouse.deliver({3999, 3});
    warehouse.deliver({4050, 4});
    warehouse.deliver({3998, 5});
    warehouse.deliver({4000, 10});
    warehouse.deliver({3999, 2});
    std::cout << warehouse.to_string() << std::endl;
    return 0;
}