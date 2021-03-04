// File: linked_list.hpp
// Created by holger on 2020/9/22.
// Linked List

#ifndef DS_LIST_LINKED_LIST_HPP
#define DS_LIST_LINKED_LIST_HPP

#include "common/abstract_list.h"
#include "common/linked_list_node.h"

// The declaration of Linked List

template<typename Entry>
class LinkedList : public ListType<Entry> {
public:
    using ListType<Entry>::notFound;

    LinkedList();

    LinkedList(const LinkedList<Entry> &) = delete;

    void operator=(const LinkedList<Entry> &) = delete;

    LinkedList(Entry dataArray[], int len);

    LinkedList(const LinkedList<Entry> &list);

    ~LinkedList() override;

    Entry &get(int index) override;

    int locate(const Entry &elem) const noexcept override;

    void insert(int index, const Entry &elem) override;

    Entry remove(int index) override;

    bool empty() const noexcept override;

    void traverse(void (*visit)(Entry &)) override;

    int length() const noexcept override;

    void clear() noexcept override;

protected:
    Node<Entry> *head;
    int size;
};

// The implement of Linked List

template<typename Entry>
LinkedList<Entry>::LinkedList()
        : head(new Node<Entry>{Entry(), nullptr}), size(0) {}

template<typename Entry>
LinkedList<Entry>::LinkedList(Entry dataArray[], int len)
        : head(new Node<Entry>{Entry(), nullptr}), size(len) {
    // copy from data array (insert after head)
    for (int i = size - 1; i >= 0; --i) {
        auto newNode = new Node<Entry>{dataArray[i], head->next};
        head->next = newNode;
    }
}

template<typename Entry>
LinkedList<Entry>::LinkedList(const LinkedList<Entry> &list)
        : head(new Node<Entry>{Entry(), nullptr}), size(list.size) {
    // copy from list (insert at the end of list)
    Node<Entry> *thisPtr = head, *otherPtr = list.head->next;
    while (otherPtr != nullptr) {
        thisPtr->next = new Node<Entry>{otherPtr->data, nullptr};
        thisPtr = thisPtr->next;
        otherPtr = otherPtr->next;
    }
}

template<typename Entry>
LinkedList<Entry>::~LinkedList() {
    while (head != nullptr) {
        auto delPtr = head;
        head = head->next;
        delete delPtr;
    }
}

template<typename Entry>
Entry &LinkedList<Entry>::get(int index) {
    if (index < 1 || index > size) {    // Legality check
        throw std::out_of_range{"The argument 'index' is out of range"};
    }
    Node<Entry> *ptr = head->next;
    while (ptr != nullptr && --index) {
        ptr = ptr->next;
    }
    return ptr->data;
}

template<typename Entry>
int LinkedList<Entry>::locate(const Entry &elem) const noexcept {
    int position = 0;
    Node<Entry> *ptr = head->next;
    while (ptr != nullptr) {
        ++position;
        if (ptr->data == elem) {
            return position;
        }
        ptr = ptr->next;
    }
    return notFound;
}

template<typename Entry>
void LinkedList<Entry>::insert(int index, const Entry &elem) {
    if (index < 1 || index > size + 1) {    // Legality check
        throw std::out_of_range{"The argument 'index' is out of range"};
    }
    Node<Entry> *ptr = head;
    // find the node in index-1
    while (ptr != nullptr && --index) {
        ptr = ptr->next;
    }
    ptr->next = new Node<Entry>{elem, ptr->next};
    ++size;
}

template<typename Entry>
Entry LinkedList<Entry>::remove(int index) {
    if (index < 1 || index > size) {    // Legality check
        throw std::out_of_range{"The argument 'index' is out of range"};
    }
    Node<Entry> *ptr = head;
    // find the node in index-1
    while (ptr != nullptr && --index) {
        ptr = ptr->next;
    }
    Node<Entry> *tempPtr = ptr->next;
    Entry elem{tempPtr->data};
    ptr->next = tempPtr->next;
    delete tempPtr;
    --size;
    return elem;
}

template<typename Entry>
bool LinkedList<Entry>::empty() const noexcept {
    return head->next == nullptr;
}

template<typename Entry>
void LinkedList<Entry>::traverse(void (*visit)(Entry &)) {
    Node<Entry> *ptr = head->next;
    while (ptr != nullptr) {
        visit(ptr->data);
        ptr = ptr->next;
    }
}

template<typename Entry>
int LinkedList<Entry>::length() const noexcept {
    return size;
}

template<typename Entry>
void LinkedList<Entry>::clear() noexcept {
    while (head->next != nullptr) {
        auto delPtr = head->next;
        head->next = delPtr->next;
        delete delPtr;
    }
    size = 0;
}

#endif //DS_LIST_LINKED_LIST_HPP
