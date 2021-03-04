// File: double_linked_list.hpp
// Created by holger on 2020/9/27.
// Double Linked List

#ifndef DS_LIST_DOUBLE_LINKED_LIST_HPP
#define DS_LIST_DOUBLE_LINKED_LIST_HPP

#include "common/abstract_list.h"
#include "common/double_linked_list_node.h"

// The declaration of Double Linked List

template<typename Entry>
class DoubleLinkedList : public ListType<Entry> {
public:
    using ListType<Entry>::notFound;

    DoubleLinkedList();

    DoubleLinkedList(const DoubleLinkedList<Entry> &) = delete;

    void operator=(const DoubleLinkedList<Entry> &) = delete;

    explicit DoubleLinkedList(Entry dataArray[], int len);

    DoubleLinkedList(const DoubleLinkedList<Entry> &list);

    ~DoubleLinkedList() override;

    int length() const noexcept override;

    Entry &get(int index) override;

    int locate(const Entry &elem) const noexcept override;

    void insert(int index, const Entry &elem) override;

    Entry remove(int index) override;

    bool empty() const noexcept override;

    void traverse(void (*visit)(Entry &)) override;

    void clear() noexcept override;

protected:
    DoubleNode<Entry> *head;
    int size;
};

// The implement of Double Linked List

template<typename Entry>
DoubleLinkedList<Entry>::DoubleLinkedList()
        : head(new DoubleNode<Entry>{nullptr, Entry(), nullptr}), size(0) {}

template<typename Entry>
DoubleLinkedList<Entry>::DoubleLinkedList(Entry dataArray[], int len)
        : head(new DoubleNode<Entry>{nullptr, Entry(), nullptr}), size(len) {
    // copy from data array (insert after head)
    for (int i = size - 1; i >= 0; --i) {
        auto newNode = new DoubleNode<Entry>{head, dataArray[i], head->next};
        if (head->next != nullptr) {
            (head->next)->prior = newNode;
        }
        head->next = newNode;
    }
}

template<typename Entry>
DoubleLinkedList<Entry>::DoubleLinkedList(const DoubleLinkedList<Entry> &list)
        : head(new DoubleNode<Entry>{nullptr, Entry(), nullptr}), size(list.size) {
    // copy from list (insert at the end of list)
    DoubleNode<Entry> *thisPtr = head, *otherPtr = list.head->next;
    while (otherPtr != nullptr) {
        thisPtr->next = new DoubleNode<Entry>{thisPtr, otherPtr->data, nullptr};
        thisPtr = thisPtr->next;
        otherPtr = otherPtr->next;
    }
}

template<typename Entry>
DoubleLinkedList<Entry>::~DoubleLinkedList() {
    while (head != nullptr) {
        auto delPtr = head;
        head = head->next;
        delete delPtr;
    }
}

template<typename Entry>
int DoubleLinkedList<Entry>::length() const noexcept {
    return size;
}

template<typename Entry>
Entry &DoubleLinkedList<Entry>::get(int index) {
    if (index < 1 || index > size) {  // Legality check
        throw std::out_of_range{"The argument 'index' is out of range"};
    }
    DoubleNode<Entry> *ptr = head->next;
    while (ptr != nullptr && --index) {
        ptr = ptr->next;
    }
    return ptr->data;
}

template<typename Entry>
int DoubleLinkedList<Entry>::locate(const Entry &elem) const noexcept {
    int position = 0;
    DoubleNode<Entry> *ptr = head->next;
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
void DoubleLinkedList<Entry>::insert(int index, const Entry &elem) {
    if (index < 1 || index > size + 1) {    // Legality check
        throw std::out_of_range{"The argument 'index' is out of range"};
    }
    DoubleNode<Entry> *ptr = head;
    // find the node in index-1
    while (ptr != nullptr && --index) {
        ptr = ptr->next;
    }
    auto newNode = new DoubleNode<Entry>{ptr, elem, ptr->next};
    if (ptr->next != nullptr) {
        (ptr->next)->prior = newNode;
    }
    ptr->next = newNode;
    ++size;
}

template<typename Entry>
Entry DoubleLinkedList<Entry>::remove(int index) {
    if (index < 1 || index > size) {    // Legality check
        throw std::out_of_range{"The argument 'index' is out of range"};
    }
    DoubleNode<Entry> *ptr = head->next;
    // find the node in index-1
    while (ptr != nullptr && --index) {
        ptr = ptr->next;
    }
    Entry elem{ptr->data};
    (ptr->prior)->next = ptr->next;
    if (ptr->next != nullptr) {
        (ptr->next)->prior = ptr->prior;
    }
    delete ptr;
    --size;
    return elem;
}

template<typename Entry>
bool DoubleLinkedList<Entry>::empty() const noexcept {
    return head->next == nullptr;
}

template<typename Entry>
void DoubleLinkedList<Entry>::traverse(void (*visit)(Entry &)) {
    DoubleNode<Entry> *ptr = head->next;
    while (ptr != nullptr) {
        visit(ptr->data);
        ptr = ptr->next;
    }
}

template<typename Entry>
void DoubleLinkedList<Entry>::clear() noexcept {
    while (head->next != nullptr) {
        auto delPtr = head->next;
        head->next = delPtr->next;
        delete delPtr;
    }
    size = 0;
}

#endif //DS_LIST_DOUBLE_LINKED_LIST_HPP
