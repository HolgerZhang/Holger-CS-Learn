// File: linked_queue.hpp
// Created by holger on 2020/10/15.
// The definition and implement of Class Template Queue

#ifndef CAT_FISHING_CYCLE_QUEUE_HPP
#define CAT_FISHING_CYCLE_QUEUE_HPP

#include <exception>
#include "node.h"

template<typename Entry>
class Queue {
public:
    Queue();

    Queue(const Queue<Entry>&) = delete;

    void operator=(const Queue<Entry>&) = delete;

    ~Queue();

    void push(Entry x);

    Entry pop();

    Entry &front();

    bool empty() const noexcept;

    void print() const noexcept;

protected:
    Node<Entry> *head, *rear;
};

template<typename Entry>
Queue<Entry>::Queue() {
    head = rear = new Node<Entry>{Entry(), nullptr};
}

template<typename Entry>
Queue<Entry>::~Queue() {
    while (head != nullptr) {
        Node<Entry> *del = head;
        head = head->next;
        delete del;
    }
}

template<typename Entry>
void Queue<Entry>::push(Entry x) {
    auto s = new Node<Entry>{x, nullptr};
    rear->next = s;
    rear = s;
}

template<typename Entry>
Entry Queue<Entry>::pop() {
    if (empty()) { throw std::underflow_error{"queue is empty"}; }
    Entry x;
    Node<Entry> *p = head->next;
    x = p->data;
    head->next = p->next;
    if (p->next == nullptr) { rear = head; }
    delete p;
    return x;
}

template<typename Entry>
Entry &Queue<Entry>::front() {
    if (empty()) { throw std::underflow_error{"queue is empty"}; }
    return head->next->data;
}

template<typename Entry>
bool Queue<Entry>::empty() const noexcept {
    return rear == head;
}

template<typename Entry>
void Queue<Entry>::print() const noexcept {
    Node<Entry> *p = head->next;
    while (p != nullptr) {
        std::cout << p->data << ' ';
        p = p->next;
    }
}

template<typename Entry>
void initializeQueue(Queue<Entry> &queue, Entry dataArray[], int size) {
    for (int i = 0; i < size; ++i) {
        queue.push(dataArray[i]);
    }
}

#endif //CAT_FISHING_CYCLE_QUEUE_HPP
