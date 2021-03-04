/**
 * @file    Node.h
 * @create  2020/05/29
 * @encoding UTF-8
 * @author  Holger
 */

#ifndef COMMON_LIST_NODE_H
#define COMMON_LIST_NODE_H

#include <string>

// 结点类(抽象基类)
class CNode {
    friend class CLinkedList;

    CNode *next_ptr; // 后继结点的地址

public:
    // 构造函数
    CNode(CNode *next = nullptr) : next_ptr(next) {}

    void insert(CNode *new_ptr); // 在当前结点之后插入一个结点
    CNode *del(); // 删除当前结点之后的后继结点, 并返回删除结点的地址

    CNode *next() { // 获取后继结点的地址
        return next_ptr;
    }

    const CNode *next() const { // 获取后继结点的地址(常函数)
        return next_ptr;
    }

    ///////////////////////
    /// 以下为（纯）虚函数 ///
    ///////////////////////

    virtual ~CNode() = default;

    virtual std::string toString() const = 0; // 将对象转换成字符串
    virtual bool operator<(const CNode &) const = 0; // 比较两节点的大小（纯虚函数）
    virtual bool operator>(const CNode &) const = 0; // 比较两节点的大小（纯虚函数）
    virtual bool operator==(const CNode &) const = 0; // 判断两节点是否相等（纯虚函数）

};

// 在当前结点之后插入一个结点
inline void CNode::insert(CNode *new_ptr) {
    new_ptr->next_ptr = this->next_ptr;
    this->next_ptr = new_ptr;
}

// 删除当前结点之后的后继结点, 并返回删除结点的地址
inline CNode *CNode::del() {
    if (next_ptr == nullptr) {
        return nullptr;
    }
    CNode *temp = next_ptr;
    next_ptr = next_ptr->next_ptr;
    return temp;
}

#endif  // COMMON_LIST_NODE_H