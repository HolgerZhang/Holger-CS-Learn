//
// Created by holger on 2020/10/5.
//

#ifndef DS_CH2_WAREHOUSE_H
#define DS_CH2_WAREHOUSE_H

#include <sstream>
#include "list/linked_list.hpp"

struct Goods {
    double price;
    int count;

    bool operator==(const Goods &goods) const;
};

class Warehouse : LinkedList<Goods> {
public:
    Warehouse() : LinkedList<Goods>() {}    // constructor
    void deliver(const Goods &goods);   // deliver the goods into warehouse
    std::string to_string() const;  // traverse the warehouse, transform into string
};


#endif //DS_CH2_WAREHOUSE_H
