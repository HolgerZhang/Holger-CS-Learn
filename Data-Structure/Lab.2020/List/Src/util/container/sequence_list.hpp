// File: sequence_list.hpp
// Created by holger on 2020/9/22.
// Sequence List

#ifndef DS_LIST_SEQUENCE_LIST_HPP
#define DS_LIST_SEQUENCE_LIST_HPP

#include "common/abstract_list.h"

// The declaration of Sequence List

template<typename Entry>
class SequenceList : public ListType<Entry> {
public:
    using ListType<Entry>::notFound;

    SequenceList() : size(0) {}

    SequenceList(Entry dataArray[], int len);

    SequenceList(const SequenceList<Entry> &list);

    ~SequenceList() override = default;

    Entry &get(int index) override;

    int locate(const Entry &elem) const noexcept override;

    void insert(int index, const Entry &elem) override;

    Entry remove(int index) override;

    bool empty() const noexcept override;

    void traverse(void (*visit)(Entry &)) override;

    int length() const noexcept override;

    void clear() noexcept override;

protected:
    static const int maxSize = 200;
    int size = 0;
    Entry data[maxSize];
};

// The implement of Sequence List

template<typename Entry>
SequenceList<Entry>::SequenceList(Entry dataArray[], int len) {
    // Legality check
    if (len > maxSize || len <= 0) {
        throw std::invalid_argument{"Invalid argument 'len' is given"};
    }
    for (int i = 0; i < len; ++i) {
        data[i] = dataArray[i];
    }
    size = len;
}

template<typename Entry>
SequenceList<Entry>::SequenceList(const SequenceList<Entry> &list) {
    size = list.size;
    for (int i = 0; i < size; ++i) {
        data[i] = list.data[i];
    }
}

template<typename Entry>
Entry &SequenceList<Entry>::get(int index) {
    // Legality check
    if (index < 1 || index > size) {
        throw std::out_of_range{"The argument 'index' is out of range"};
    }
    return data[index - 1];
}

template<typename Entry>
int SequenceList<Entry>::locate(const Entry &elem) const noexcept {
    for (int i = 0; i < size; ++i) {
        if (data[i] == elem) {
            return i + 1;
        }
    }
    return notFound;
}

template<typename Entry>
void SequenceList<Entry>::insert(int index, const Entry &elem) {
    // Legality check
    if (size >= maxSize) {
        throw std::overflow_error{"The length of this list has been the maximum"};
    }
    if (index < 1 || index > size + 1) {
        throw std::out_of_range{"The argument 'index' is out of range"};
    }
    for (int i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index - 1] = elem;
    ++size;
}

template<typename Entry>
Entry SequenceList<Entry>::remove(int index) {
    // Legality check
    if (size <= 0) {
        throw std::underflow_error{"The length of this list has been the minimum"};
    }
    if (index < 1 || index > size) {
        throw std::out_of_range{"The argument 'index' is out of range"};
    }
    Entry elem{data[index - 1]};
    for (int i = index; i < size; ++i) {
        data[i - 1] = data[i];
    }
    --size;
    return elem;
}

template<typename Entry>
bool SequenceList<Entry>::empty() const noexcept {
    return size == 0;
}

template<typename Entry>
void SequenceList<Entry>::traverse(void (*visit)(Entry &)) {
    for (int i = 0; i < size; ++i) {
        visit(data[i]);
    }
}

template<typename Entry>
int SequenceList<Entry>::length() const noexcept {
    return size;
}

template<typename Entry>
void SequenceList<Entry>::clear() noexcept {
    size = 0;
}

#endif //DS_LIST_SEQUENCE_LIST_HPP
