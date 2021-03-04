// File: linked_list_node.h
// Created by holger on 2020/9/22.
// The node of linked list

#ifndef DS_LIST_LINKED_LIST_NODE_H
#define DS_LIST_LINKED_LIST_NODE_H

template<typename Entry>
struct Node {
    Entry data;
    Node<Entry> *next;
};

#endif //DS_LIST_LINKED_LIST_NODE_H
