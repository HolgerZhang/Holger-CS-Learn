#ifndef CAT_FISHING_NODE_H
#define CAT_FISHING_NODE_H

template<typename Entry>
struct Node {
    Entry data;
    Node<Entry> *next;
};

#endif //CAT_FISHING_NODE_H
