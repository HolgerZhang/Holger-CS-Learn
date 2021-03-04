#ifndef TREE_BINARY_SEARCH_TREE_HPP
#define TREE_BINARY_SEARCH_TREE_HPP

#include "binary_tree.hpp"

namespace tree {

    /**
     * Binary Search Tree Class
     * @superclass Class BinaryTree
     */
    template<typename Record>
    class BinarySearchTree : public BinaryTree<Record> {
    public:
        bool search(Record &target) const;  // Find target in the tree.
        bool insert(const Record &newData); // Insert data into the tree.
        bool remove(const Record &oldData); // Remove data into the tree.
        void create(const std::vector<Record> &container); // create BST.
    protected:
        // Methods called recursively:
        static BinaryNode <Record> *recursiveSearchNode(BinaryNode <Record> *subRoot, const Record &target);

        static bool recursiveSearchInsert(BinaryNode <Record> *&subRoot, const Record &newData);

        static bool recursiveSearchRemove(BinaryNode <Record> *&subRoot, const Record &target);

        // Remove the root of the subtree in such a way that the properties of a binary search tree are preserved.
        static void removeRoot(BinaryNode <Record> *&subRoot);
    };

}

/**
 * search method
 * @post find target in the tree, and target will contain more information if found.
 * @uses The function recursiveSearchNode
 * @param target The data to search
 * @return true if found target in tree, or false if target not present in the tree.
 */
template<typename Record>
bool tree::BinarySearchTree<Record>::search(Record &target) const {
    BinaryNode<Record> *found = recursiveSearchNode(this->root, target);
    if (found == nullptr) { return false; }
    target = found->data;
    return true;
}

/**
 * recursiveSearchNode function
 * @post find target in the sub tree, and target will contain more information if found.
 * @uses The function recursiveSearchNode recursively
 * @param subRoot The root node of tree or subtree
 * @param target The data to search
 * @return BinaryNode<> pointer whose data equals target, or nullptr if not found.
 */
template<typename Record>
tree::BinaryNode<Record> *
tree::BinarySearchTree<Record>::recursiveSearchNode(BinaryNode <Record> *subRoot, const Record &target) {
    if (subRoot == nullptr) { return nullptr; } // Empty tree
    if (subRoot->data == target) { return subRoot; }  // Found
    if (target < subRoot->data) { return recursiveSearchNode(subRoot->left, target); }
    return recursiveSearchNode(subRoot->right, target);
}

/**
 * insert method
 * @uses The function recursiveSearchInsert
 * @param newData The data to insert
 * @return true if newData insert into the tree, or false if newData is already in the tree.
 */
template<typename Record>
bool tree::BinarySearchTree<Record>::insert(const Record &newData) {
    return recursiveSearchInsert(this->root, newData);
}

/**
 * recursiveSearchInsert function
 * @post Search newData and insert newData in the tree rooted at subRoot.
 * @uses The function recursiveSearchInsert recursively
 * @param subRoot The root node of tree or subtree
 * @param newData The data to insert
 * @return true if newData insert into the tree, or false if newData is already in the tree.
 */
template<typename Record>
bool tree::BinarySearchTree<Record>::recursiveSearchInsert(BinaryNode <Record> *&subRoot, const Record &newData) {
    if (subRoot == nullptr) {   // Found, insert
        subRoot = new BinaryNode<Record>(newData);
        return true;
    } else if (newData < subRoot->data) {
        return recursiveSearchInsert(subRoot->left, newData);
    } else if (newData > subRoot->data) {
        return recursiveSearchInsert(subRoot->right, newData);
    }
    return false;   // newData == subRoot->data, newData is already in the tree
}

/**
 * remove method
 * @uses The function recursiveSearchRemove
 * @param oldData The data to remove
 * @return true if a Record with a key matching that of target belongs to the BinarySearchTree,
 *         and the corresponding node is removed from the tree. Otherwise, false is returned.
 */
template<typename Record>
bool tree::BinarySearchTree<Record>::remove(const Record &oldData) {
    return recursiveSearchRemove(this->root, oldData);
}

/**
 * recursiveSearchRemove function
 * @pre subRoot is either nullptr or points to a subtree of the BinarySearchTree.
 * @uses the function recursiveSearchRemove recursively and the function removeRoot
 * @param subRoot The root node of tree or subtree
 * @param target The data to remove
 * @return false if target is not in the subtree. Otherwise, the subtree node containing target has been removed
 *         in such a way that the properties of a binary search tree are preserved, and true is returned.
 */
template<typename Record>
bool tree::BinarySearchTree<Record>::recursiveSearchRemove(BinaryNode <Record> *&subRoot, const Record &target) {
    if (subRoot == nullptr) { return false; } // Empty tree
    else if (subRoot->data == target) { // Found, remove
        removeRoot(subRoot);
        return true;
    } else if (target < subRoot->data) {
        return recursiveSearchRemove(subRoot->left, target);
    }
    return recursiveSearchRemove(subRoot->right, target);
}

/**
 * removeRoot function
 * @pre subRoot is a original pointer(not NULL) to a subtree of the BinarySearchTree.
 * @post The root of the subtree is removed in such a way that the properties of a binary search tree are preserved.
 *       The parameter subRoot is reset as the root of the modified subtree.
 * @param subRoot The root node of tree or subtree
 */
template<typename Record>
void tree::BinarySearchTree<Record>::removeRoot(BinaryNode <Record> *&subRoot) {
    BinaryNode<Record> *toDelete = subRoot;
    if (subRoot->right == nullptr) { subRoot = subRoot->left; }
    else if (subRoot->left == nullptr) { subRoot = subRoot->right; }
    else {  // Neither subtree is empty
        toDelete = subRoot->left;   // Find the max node in the left sub tree
        BinaryNode<Record> *parent = subRoot;   // parent of toDelete
        while (toDelete->right != nullptr) {    // Find the right bottom node
            parent = toDelete;
            toDelete = toDelete->right;
        } // end while
        subRoot->data = toDelete->data;     // Move data from toDelete to root
        if (parent == subRoot) {
            subRoot->left = toDelete->left;
        } else {
            parent->right = toDelete->left;
        }
    }
    delete toDelete;
}

template<typename Record>
void tree::BinarySearchTree<Record>::create(const std::vector<Record> &container) {
    for (const Record &data : container) { recursiveSearchInsert(this->root, data); }
}

#endif //TREE_BINARY_SEARCH_TREE_HPP
