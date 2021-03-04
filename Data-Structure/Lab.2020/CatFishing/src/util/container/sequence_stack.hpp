// File: sequence_stack.hpp
// Created by holger on 2020/10/1.
// The definition and implement of Class Template Stack

#ifndef CAT_FISHING_SEQUENCE_STACK_HPP
#define CAT_FISHING_SEQUENCE_STACK_HPP

#include <iostream>
#include <stdexcept>
#include <cstring>

// Sequential stack Template Class
template<typename Entry>
class Stack {
public:
    Stack();

    Stack(const Stack<Entry> &other);

    ~Stack() = default;

    void push(const Entry &elem);

    Entry pop();

    Entry &top();

    bool empty() const noexcept;

    bool full() const noexcept;

    void clear() noexcept;

    void print() const noexcept;

protected:
    static const int stackSize = 256;
    Entry data[stackSize];
    int current;
};

template<typename Entry>
Stack<Entry>::Stack() : current(-1) {}


template<typename Entry>
Stack<Entry>::Stack(const Stack<Entry> &other) : current(other.current) {
    for (int i = 0; i < current + 1; ++i) {
        data[i] = other.data[i];
    }
}

template<typename Entry>
void Stack<Entry>::push(const Entry &elem) {
    if (full()) {
        throw std::overflow_error{"stack is full"};
    }
    data[++current] = elem;
}

template<typename Entry>
Entry Stack<Entry>::pop() {
    if (empty()) {
        throw std::underflow_error{"stack is empty"};
    }
    return data[current--];
}

template<typename Entry>
Entry &Stack<Entry>::top() {
    if (empty()) {
        throw std::underflow_error{"stack is empty"};
    }
    return data[current];
}

template<typename Entry>
bool Stack<Entry>::empty() const noexcept {
    return current <= -1;
}

template<typename Entry>
bool Stack<Entry>::full() const noexcept {
    return current >= stackSize - 1;
}

template<typename Entry>
void Stack<Entry>::clear() noexcept {
    current = -1;
}

template<typename Entry>
void Stack<Entry>::print() const noexcept {
    for (int i = 0; i <= current; ++i) {
        std::cout << data[i] << ' ';
    }
}

template<typename Entry>
void initializeStack(Stack<Entry> &stack, Entry dataArray[], int size) {
    for (int i = 0; i < size; ++i) {
        stack.push(dataArray[i]);
    }
}

#endif //CAT_FISHING_SEQUENCE_STACK_HPP
