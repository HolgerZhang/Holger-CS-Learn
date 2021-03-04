/**
 * @file    LinkedList.cpp
 * @create  2020/05/29
 * @encoding UTF-8
 * @author  Holger
 */

#include "LinkedList.h"

using namespace std;

// 表示未找到或为空（空指针）
CNode *CLinkedList::None = nullptr;

// 释放结点
void CLinkedList::free(CNode *ptr) {
    delete ptr;
}

// 默认构造函数
CLinkedList::CLinkedList() : head(nullptr), end(nullptr), m_length(0) {}

// 析构函数
CLinkedList::~CLinkedList() {
    clear();
}

// 获取元素个数
int CLinkedList::length() const {
    return m_length;
}

// 判断是否为空链表
bool CLinkedList::isEmpty() const {
    return (m_length == 0);
}

// 返回首个满足结点数据的引用
CNode *CLinkedList::find(const CNode &data) {
    for (auto p = head; p != nullptr; p = p->next_ptr) {
        if (*p == data) {
            return p;
        }
    }
    return None;
}

// 将链表转换成字符串
std::string CLinkedList::toString() const {
    ostringstream out;
    out << "[";
    for (auto p = head; p != nullptr; p = p->next_ptr) {
        out << p->toString();
        if (p->next_ptr != nullptr) {
            out << ", ";
        }
    }
    out << ']';
    return out.str();
}

// 获取表头元素的指针
CNode *CLinkedList::front() {
    if (isEmpty()) {
        return None;
    }
    return head;
}

// 获取表尾元素的指针
CNode *CLinkedList::back() {
    if (isEmpty()) {
        return None;
    }
    return end;
}

// 获取下标为pos的元素，由[]调用
CNode &CLinkedList::at(int pos) {
    if (pos < 0 || pos >= m_length) {
        throw out_of_range("index out of range");
    }
    auto p = head;
    for (int i = 0; i < pos; ++i) { // 找到指定下标的元素
        p = p->next_ptr;
    }
    return *p;
}

const CNode &CLinkedList::at(int pos) const {
    if (pos < 0 || pos >= m_length) {
        throw out_of_range("index out of range");
    }
    auto p = head;
    for (int i = 0; i < pos; ++i) { // 找到指定下标的元素
        p = p->next_ptr;
    }
    return *p;
}

// 重载下标运算符
CNode &CLinkedList::operator[](int pos) {
    return at(pos);
}

const CNode &CLinkedList::operator[](int pos) const {
    return at(pos);
}

// 在表头插入结点
void CLinkedList::push_front(CNode *new_item) {
    if (isEmpty()) {
        new_item->next_ptr = nullptr;
        head = new_item;
        end = new_item;
    } else {
        new_item->next_ptr = head;
        head = new_item;
    }
    m_length++;
}

// 在表尾插入结点
void CLinkedList::push_back(CNode *new_item) {
    if (isEmpty()) {
        new_item->next_ptr = nullptr;
        head = new_item;
        end = new_item;
    } else {
        new_item->next_ptr = nullptr;
        end->next_ptr = new_item;
        end = new_item;
    }
    m_length++;
}

// 删除表头结点
void CLinkedList::pop_front() {
    if (isEmpty()) {
        return;
    }
    auto temp = head->next_ptr;
    free(head);
    head = temp;
    m_length--;
}

// 删除表尾结点
void CLinkedList::pop_back() {
    if (isEmpty()) {
        return;
    }
    auto p = head;
    for (int i = 1; i < m_length - 1; ++i) { // 找到倒数第二个元素
        p = p->next_ptr;
    }
    p->next_ptr = nullptr;
    free(end);
    end = p;
    m_length--;
}

// 在指定下标后插入结点
void CLinkedList::insert(int pos, CNode *new_item) {
    if (isEmpty() && (pos < 0 || pos >= m_length)) {
        throw out_of_range("index out of range");
    }
    auto p = head;
    for (int i = 0; i < pos; ++i) { // 找到指定下标的元素
        p = p->next_ptr;
    }
    auto temp = p->next_ptr;
    p->next_ptr = new_item;
    new_item->next_ptr = temp;
    m_length++;
}

// 删除指定下标对应的结点
void CLinkedList::pop(int pos) {
    if (isEmpty() && (pos < 0 || pos >= m_length)) {
        throw out_of_range("index out of range");
    }
    if (pos == 0) {
        pop_front();
        return;
    }
    auto p = head;
    for (int i = 0; i < pos - 1; ++i) { // 找到指定下标的前一个元素
        p = p->next_ptr;
    }
    auto temp = p->next_ptr->next_ptr;
    free(p->next_ptr);
    p->next_ptr = temp;
    m_length--;
}

// 清空链表并释放所有结点的内存空间, 但保留链表对象. 也被析构函数调用
void CLinkedList::clear() {
    while (!isEmpty()) {
        pop_front();
    }
}

// 原地排序
void CLinkedList::sort(bool reverse) {
    // for (int index = 0; index < m_length - 1; ++index) {
    // 	int temp = index;
    // 	while (index >= 0) {
    // 		CNode &left = at(index), &right = at(index + 1);
    // 		if (!reverse) {
    //          if (left > right) {
    // 		        left.swap(right);
    //          }
    // 		}
    // 		else {
    // 			if (left < right) {
    // 				left.swap(right);
    // 			}
    // 		}
    // 		index--;
    // 	}
    // 	index = temp;
    // }
    for (int i = 0; i < m_length - 1; i++) {
        CNode *curr = head, *prev = None;
        int do_swap = 0;
        for (int j = 0; j < m_length - i - 1; j++) {
            if (!reverse) {
                if (*curr > *curr->next_ptr) {
                    do_swap = 1;
                }
            } else {
                if (*curr < *curr->next_ptr) {
                    do_swap = 1;
                }
            }

            if (do_swap) {
                CNode *temp = curr->next_ptr;
                curr->next_ptr = curr->next_ptr->next_ptr;
                temp->next_ptr = curr;
                if (prev == None) {
                    head = temp;
                    prev = head;
                } else {
                    prev->next_ptr = temp;
                    prev = temp;
                }
                do_swap = 0;
            } else {
                prev = curr;
                curr = curr->next_ptr;
            }

        }

        end = &at(m_length - 1);

    }

}


std::ostream &operator<<(std::ostream &out, const CLinkedList &list) {
    out << list.toString();
    return out;
}
