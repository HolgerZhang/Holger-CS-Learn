/**
 * @file    LinkedList.h
 * @create  2020/05/29
 * @encoding UTF-8
 * @author  Holger
 */

#ifndef COMMON_LIST_LINKED_LIST_H
#define COMMON_LIST_LINKED_LIST_H

#include <iostream>
#include <sstream>
#include "Node.h"

// 链表类
class CLinkedList {
private:
    CNode *head, *end; // 表头和表尾指针
    int m_length; // 元素的个数

    // // 生成新的结点
    // CNode* createNode(CNode* next = nullptr); // 未能实现

    // 释放结点
    static void free(CNode *ptr);

    // // 复制链表L到当前链表(假设为空), 由复制构造函数和operator=调用
    // void copy(const CLinkedList& list); // 未能实现

public:
    static CNode *None; // 表示未找到或为空（空指针）

    // 默认构造函数
    CLinkedList();

    // // 复制构造函数
    // CLinkedList(const CLinkedList&); // 未能实现

    // 析构函数
    ~CLinkedList();

    //////////////////
    /// 基础数据接口 ///
    //////////////////

    // 获取元素个数
    int length() const;

    // 判断是否为空链表
    bool isEmpty() const;

    // 返回首个满足结点数据的指针
    CNode *find(const CNode &data);

    // 将链表转换成字符串
    std::string toString() const;

    // 获取表头元素的指针
    CNode *front();

    // 获取表尾元素的指针
    CNode *back();

    // 获取下标为pos的元素，由[]调用
    CNode &at(int pos);

    const CNode &at(int pos) const;


    //////////////////
    /// 数据操作方法 ///
    //////////////////

    // 在表头插入结点
    void push_front(CNode *new_item);

    // 在表尾插入结点
    void push_back(CNode *new_item);

    // 删除表头结点
    void pop_front();

    // 删除表尾结点
    void pop_back();

    // 在指定下标后插入结点
    void insert(int pos, CNode *new_item);

    // 删除指定下标对应的结点
    void pop(int pos);

    // // 用一个链表对象扩展本对象
    // void extend(const CLinkedList &list); // 未能实现
    // // 获得链表的深拷贝对象，可由复制构造函数调用
    // CLinkedList& copy(); // 未能实现

    // 清空链表并释放所有结点的内存空间, 但保留链表对象. 也被析构函数调用
    void clear();

    // 原地排序
    void sort(bool reverse = false);

    /////////////////
    /// 重载运算符 ///
    /////////////////

    // // 重载赋值运算符
    // CLinkedList &operator=(const CLinkedList &list); // 未能实现

    // 重载下标运算符
    CNode &operator[](int pos);

    const CNode &operator[](int pos) const;

    // // 重载+运算符, 返回拼接的两个链表
    // CLinkedList operator+(const CLinkedList &list) const ;  // 未能实现
    // // 重载+=运算符，拼接两个链表
    // CLinkedList &operator+=(CLinkedList &list); // 未能实现

};


// 链表输出函数
std::ostream &operator<<(std::ostream &out, const CLinkedList &list);


#endif  // COMMON_LIST_LINKED_LIST_H