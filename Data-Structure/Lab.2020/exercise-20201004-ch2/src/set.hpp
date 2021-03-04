//
// Created by holger on 2020/10/4.
//

#ifndef DS_CH2_CH2_SET_HPP
#define DS_CH2_CH2_SET_HPP

#include "list/linked_list.hpp"

// Class Set inherited from Class Template LinkedList
template<typename Entry>
class Set : public LinkedList<Entry> {
public:
    using LinkedList<Entry>::notFound;

    // constructors
    Set();

    Set(Entry dataArray[], int len);

    Set(const Set<Entry> &list);

    // override insert method, ensure the uniqueness of the elements in set
    void insert(int index, const Entry &elem) override;

    // the difference set
    Set<Entry> set_difference(const Set<Entry> &set) const;

    // the intersection set
    Set<Entry> set_intersection(const Set<Entry> &set) const;

    // union set
    Set<Entry> set_union(const Set<Entry> &set) const;

    // judge whether object is a subset
    bool is_subset(const Set<Entry> &set) const;

    // judge whether object is a superset
    bool is_superset(const Set<Entry> &set) const;
};

template<typename Entry>
Set<Entry>::Set() : LinkedList<Entry>() {}

template<typename Entry>
Set<Entry>::Set(Entry dataArray[], int len) {
    this->head = new Node<Entry>{Entry(), nullptr};
    this->size = len;
    for (int i = this->size - 1; i >= 0; --i) { // find the elem
        if (this->locate(dataArray[i]) != Set<Entry>::notFound) {
            this->size--;
            continue;
        }
        auto newNode = new Node<Entry>{dataArray[i], this->head->next};
        this->head->next = newNode;
    }
}

template<typename Entry>
Set<Entry>::Set(const Set<Entry> &list)
        : LinkedList<Entry>((const LinkedList<Entry> &) list) {}

template<typename Entry>
void Set<Entry>::insert(int index, const Entry &elem) {
    int position = this->locate(elem);
    if (position == Set<Entry>::notFound) {  // only insert when elem is not found
        LinkedList<Entry>::insert(index, elem);
        return;
    } else if (position == index) {
        return;
    }
    throw std::runtime_error{"'elem' is already in the set, position is "
                             + std::to_string(position)};
}

template<typename Entry>
Set<Entry> Set<Entry>::set_difference(const Set<Entry> &set) const {
    Set<Entry> result;
    Node<Entry> *ptr = this->head->next;
    while (ptr != nullptr) {
        if (set.locate(ptr->data) == Set<Entry>::notFound) {    // set up the difference set
            result.insert(1, ptr->data);
        }
        ptr = ptr->next;
    }
    return result;
}

template<typename Entry>
Set<Entry> Set<Entry>::set_intersection(const Set<Entry> &set) const {
    Set<Entry> result;
    Node<Entry> *ptr = this->head->next;
    while (ptr != nullptr) {
        if (set.locate(ptr->data) != Set<Entry>::notFound) {    // set up the intersection set
            result.insert(1, ptr->data);
        }
        ptr = ptr->next;
    }
    return result;
}

template<typename Entry>
Set<Entry> Set<Entry>::set_union(const Set<Entry> &set) const {
    Set<Entry> result(*this);
    Node<Entry> *ptr = set.head->next;
    while (ptr != nullptr) {
        if (result.locate(ptr->data) == Set<Entry>::notFound) { // set up the union set
            result.insert(1, ptr->data);
        }
        ptr = ptr->next;
    }
    return result;
}

template<typename Entry>
bool Set<Entry>::is_subset(const Set<Entry> &set) const {
    Node<Entry> *ptr = this->head->next;
    while (ptr != nullptr) {
        // judge whether object is a subset
        if (set.locate(ptr->data) == Set<Entry>::notFound) {
            return false;
        }
        ptr = ptr->next;
    }
    return true;
}

template<typename Entry>
bool Set<Entry>::is_superset(const Set<Entry> &set) const {
    return set.is_subset(*this);
}


#endif //DS_CH2_CH2_SET_HPP
