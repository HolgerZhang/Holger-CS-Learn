// File: double_linked_list_node.h
// Created by holger on 2020/9/27.
// The node of double linked list

#ifndef DS_LIST_DOUBLE_LINKED_LIST_NODE_H
#define DS_LIST_DOUBLE_LINKED_LIST_NODE_H

template<typename Entry>
struct DoubleNode {
    DoubleNode<Entry> *prior;
    Entry data;
    DoubleNode<Entry> *next;
};

#endif //DS_LIST_DOUBLE_LINKED_LIST_NODE_H
