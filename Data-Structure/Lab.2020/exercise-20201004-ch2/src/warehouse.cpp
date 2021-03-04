//
// Created by holger on 2020/10/5.
//
#include <cstdlib>
#include "warehouse.h"

bool Goods::operator==(const Goods &goods) const {
    return std::abs(price - goods.price) < 1e-9;
}

void Warehouse::deliver(const Goods &goods) {
    if (empty()) {
        head->next = new Node<Goods>{goods, head->next};
        ++size;
        return;
    }
    Node<Goods> *pre = head, *next = head->next;
    while (next != nullptr) {
        if (next->data.price > goods.price) {  // insert by order
            pre->next = new Node<Goods>{goods, pre->next};
            ++size;
            return;
        } else if (next->data == goods) {  // update count
            next->data.count += goods.count;
            return;
        }
        pre = pre->next;
        next = next->next;
    }
    pre->next = new Node<Goods>{goods, pre->next};
    ++size;
}

std::string Warehouse::to_string() const {
    std::ostringstream out;
    Node<Goods> *ptr = head->next;
    out << "Warehouse: { ";
    while (ptr != nullptr) {
        out << "$" << ptr->data.price << ": " << ptr->data.count;
        ptr = ptr->next;
        if (ptr != nullptr) {
            out << ", ";
        }
    }
    out << " }";
    return out.str();
}
