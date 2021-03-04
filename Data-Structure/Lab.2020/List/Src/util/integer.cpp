// File: integer.cpp
// Created by holger on 2020/9/23.
// The implement of BigInteger

#include "integer.h"

BigInteger::BigInteger() : LinkedList<int>(), sign(IntegerSign::positive) {
    head->next = new Node<int>{0, nullptr};
    size = 1;
}

BigInteger::BigInteger(const BigInteger &integer)
        : LinkedList<int>((const LinkedList &) integer), sign(integer.sign) {}

BigInteger::BigInteger(const std::string &str) : LinkedList<int>(), sign(IntegerSign::positive) {
    if (str.empty()) {
        head->next = new Node<int>{0, nullptr};
        size = 1;
        return;
    }
    Node<int> *ptr = head;
    for (auto p = str.rbegin(); p != str.rend(); ++p) {
        if (*p == '-') {
            if (p == str.rbegin()) {    // Legality check
                throw std::invalid_argument{"Invalid argument 'str' is given"};
            }
            sign = IntegerSign::negative;
            return;
        }
        if (*p < '0' || *p > '9') {  // Legality check
            throw std::invalid_argument{"Invalid argument 'str' is given"};
        }
        ptr->next = new Node<int>{(int) (*p - '0'), nullptr};
        ptr = ptr->next;
        ++size;
    }
}

std::string BigInteger::to_string() const {
    std::string str;
    Node<int> *ptr = head->next;
    while (ptr != nullptr) {
        str.insert(str.begin(), (char) ('0' + ptr->data));
        ptr = ptr->next;
    }
    auto p = str.begin();
    while (p != str.end()) {    // remove leading zeros
        if (*p != '0') {
            break;
        }
        p = str.erase(p);
    }
    if (str.length() == 0) {    // empty or 0 Integer
        return "0";
    }
    if (sign == IntegerSign::negative) {    // sign of integer
        str.insert(str.begin(), '-');
    }
    return str;
}

BigInteger BigInteger::plus(const BigInteger &other) const {
    BigInteger integer(*this);
    return integer.self_plus(other);
}

BigInteger &BigInteger::self_plus(const BigInteger &other) {
    if (sign == other.sign) {   // sign of integer is same
        auto p = head->next, q = other.head->next;
        while (p != nullptr && q != nullptr) {
            if (p->next == nullptr) {   // Expand storage space
                p->next = new Node<int>{0, nullptr};
                ++size;
            }
            p->data += q->data;
            if (p->data >= 10) {    // put it into next bit
                (p->next)->data += p->data / 10;
                p->data %= 10;
            }
            p = p->next;
            q = q->next;
        }
        // Tail treatment
        while (p != nullptr) {
            if (p->data >= 10) {
                if (p->next == nullptr) {
                    p->next = new Node<int>{0, nullptr};
                    ++size;
                }
                (p->next)->data += p->data / 10;
                p->data %= 10;
            }
            p = p->next;
        }
    } else {    // sign of integer is different, call `minus`
        BigInteger integer(other);
        integer.change_sign();
        self_minus(integer);
    }
    return *this;
}

BigInteger BigInteger::multiply(const BigInteger &other) const {
    BigInteger integer(*this);
    return integer.self_multiply(other);
}

BigInteger &BigInteger::self_multiply(const BigInteger &other) {
    const BigInteger left(*this);   // left operand
    clear();
    insert(1, 0);   // this = 0
    auto ptr = other.head->next;
    int cnt = 0;
    while (ptr != nullptr) {
        BigInteger mid_result;
        do_multiply(left, ptr->data, mid_result);
        for (int i = 0; i < cnt; ++i) { // Enlargement factor
            mid_result.insert(1, 0);
        }
        ++cnt;
        self_plus(mid_result);
        ptr = ptr->next;
    }
    // Sign processing
    if (left.sign == other.sign) {
        sign = IntegerSign::positive;
    } else {
        sign = IntegerSign::negative;
    }
    return *this;
}

BigInteger BigInteger::minus(const BigInteger &other) const {
    BigInteger integer(*this);
    return integer.self_minus(other);
}

BigInteger &BigInteger::self_minus(const BigInteger &other) {
    if (sign == other.sign) {   // sign of integer is same
        // make sure this > other
        if (this->abs_little_than(other)) {
            // abs(this) < abs(other)
            // swap this and other
            const BigInteger right(*this);
            clear();
            insert(1, 0);  // this = 0
            self_plus(other);
            // swap finished, do this - right
            do_minus(*this, right);
            change_sign(); // take the opposite
        } else {
            // this >= other, do this - other
            do_minus(*this, other);
        }
    } else {    // sign of integer is different, call `plus`
        BigInteger integer(other);
        integer.change_sign();
        self_plus(integer);
    }
    return *this;
}

void BigInteger::do_minus(BigInteger &left, const BigInteger &right) {
    // do minus calculation, left >= right
    auto p = left.head->next, q = right.head->next;
    while (p != nullptr && q != nullptr) {
        p->data -= q->data;
        if (p->data < 0) {  // Borrow 10 from the previous
            (p->next)->data -= 1;
            p->data += 10;
        }
        p = p->next;
        q = q->next;
    }
    // Tail treatment
    while (p != nullptr) {
        if (p->data < 0) {
            (p->next)->data -= 1;
            p->data += 10;
        }
        p = p->next;
    }
}

void BigInteger::change_sign() {
    switch (sign) {
        case IntegerSign::positive:
            sign = IntegerSign::negative;
            break;
        case IntegerSign::negative:
            sign = IntegerSign::positive;
            break;
    }
}

bool BigInteger::abs_little_than(const BigInteger &other) const {
    std::string integer1 = this->to_string(), integer2 = other.to_string();
    // erase '-'
    if (integer1[0] == '-') {
        integer1.erase(0, 1);
    }
    if (integer2[0] == '-') {
        integer2.erase(0, 1);
    }
    // compare
    if (integer1.length() == integer2.length()) {
        return integer1 < integer2;
    }
    return integer1.length() < integer2.length();
}

void BigInteger::do_multiply(const BigInteger &left, int right, BigInteger &result) {
    if (right == 0) {
        return;
    }
    auto p = left.head->next, q = result.head->next;
    int next_bit = 0;
    while (p != nullptr) {
        q->data = p->data * right + next_bit;
        if (q->data >= 10) {    // put it into `next_bit`
            next_bit = q->data / 10;
            q->data %= 10;
        } else {    // `next_bit` = 0
            next_bit = 0;
        }
        // Expand storage space
        q->next = new Node<int>{0, nullptr};
        result.size++;
        p = p->next;
        q = q->next;
    }
    // Tail treatment
    if (next_bit != 0) {
        q->data = next_bit;
    }
}
