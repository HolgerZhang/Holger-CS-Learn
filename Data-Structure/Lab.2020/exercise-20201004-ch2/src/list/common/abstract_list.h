// File: abstract_list.h
// Created by holger on 2020/9/22.
// The Interface of ListType

#ifndef DS_LIST_ABSTRACT_LIST_H
#define DS_LIST_ABSTRACT_LIST_H

#include <stdexcept>

/**
 * The Interface of ListType (Abstract Class)
 * @tparam Entry    The type of contents in the list.
 * @implements
 * <li> static constexpr `notFound`: int -> Returned when the head not found in the list. </li>
 * <li> default CONSTRUCTOR (required) -> Create an empty list. </li>
 * <li> CONSTRUCTOR(array: Entry[], len: int) (explicit) -> Initialize the list by Entry array. </li>
 * <li> copy CONSTRUCTOR (required) </li>
 * <li> method DESTRUCTOR (required) </li>
 * <li> method length(): int const (noexcept) -> Return the length of the list. </li>
 * <li> method get(index: int): Entry const -> Find item by index,
 *                                             throw `out_of_range` when `index` is invalid. </li>
 * <li> method locate(item: Entry): int const (noexcept) -> Locate the index of the entry,
 *                                                           return `notFound` when the item not found in the list.</li>
 * <li> method insert(index: int, item: Entry) -> Insert entry on the position of `index`,
 *                                                throw `index_error` when `index` is invalid. </li>
 * <li> method remove(index: int): Entry -> Remove the entry on the position of `index`, and return it,
 *                                          throw `index_error` when `index` is invalid. </li>
 * <li> method empty(): bool const (noexcept) -> Judge the list is empty or not. </li>
 * <li> method traverse(visit: function pointer typed void and required Entry& as the only parameter)
 *                                               -> Traverse the list by `visit`. </li>
 * <li> method clear() (noexcept) -> clear the list, and remain the head. </li>
 */
template<typename Entry>
class ListType {
public:
    virtual ~ListType() = default;

    virtual int length() const noexcept = 0;

    virtual Entry &get(int index) = 0;

    virtual int locate(const Entry &elem) const noexcept = 0;

    virtual void insert(int index, const Entry &elem) = 0;

    virtual Entry remove(int index) = 0;

    virtual bool empty() const noexcept = 0;

    virtual void traverse(void (*visit)(Entry &)) = 0;

    virtual void clear() noexcept = 0;

    static const int notFound;
};

template<typename Entry>
const int ListType<Entry>::notFound = 0;

#endif //DS_LIST_ABSTRACT_LIST_H
