#ifndef TREE_BINARY_NODE_HPP
#define TREE_BINARY_NODE_HPP

namespace tree {

    /**
     * Binary Node Class
     */
    template<typename Entry>
    struct BinaryNode {
        Entry data;     // Data
        BinaryNode<Entry> *left;    // Left Tree Node
        BinaryNode<Entry> *right;   // Right Tree Node
        BinaryNode() : data(Entry()), left(nullptr), right(nullptr) {}  // Default constructor
        explicit BinaryNode(const Entry &data)   // Copy constructor
                : data(data), left(nullptr), right(nullptr) {}
    };

}

#endif //TREE_BINARY_NODE_HPP
