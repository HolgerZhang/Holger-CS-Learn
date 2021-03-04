// File: integer.h
// Created by holger on 2020/9/23.
// The declaration of BigInteger and IntegerSign

#ifndef DS_LIST_INTEGER_LINKED_H
#define DS_LIST_INTEGER_LINKED_H

#include <ostream>
#include <string>
#include <stdexcept>
#include "container/linked_list.hpp"

enum class IntegerSign {
    positive, negative
};

class BigInteger : LinkedList<int> {
public:
    BigInteger();

    BigInteger(const std::string &str);

    BigInteger(const BigInteger &integer);

    std::string to_string() const;

    BigInteger plus(const BigInteger &other) const;

    BigInteger &self_plus(const BigInteger &other);

    BigInteger multiply(const BigInteger &other) const;

    BigInteger &self_multiply(const BigInteger &other);

    BigInteger minus(const BigInteger &other) const;

    BigInteger &self_minus(const BigInteger &other);

private:
    IntegerSign sign;

    void change_sign();

    bool abs_little_than(const BigInteger &other) const;

    static void do_minus(BigInteger &left, const BigInteger &right);

    static void do_multiply(const BigInteger &left,
                            int right,
                            BigInteger &result);
};

#endif //DS_LIST_INTEGER_LINKED_H
