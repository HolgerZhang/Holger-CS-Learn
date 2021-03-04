#ifndef TREE_BINARY_TREE_HPP
#define TREE_BINARY_TREE_HPP

#include <queue>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "binary_node.hpp"

namespace tree {

    /**
     * Binary Tree Class
     * @uses Class BinaryNode as inner pointer;
     *       Class std::queue when traversing in levelOrder sequence and calculating tree width;
     *       Functiontion std::max to calculate the max number;
     *       Functiontion std::find to find root node position in inorder sequence;
     *       Class std::vector as Container.
     */
    template<typename Entry>
    class BinaryTree {
    public:
        // Constructor and Destructor:
        BinaryTree();   // Constructor
        BinaryTree(const BinaryTree<Entry> &original);  // Copy constructor
        BinaryTree<Entry> &operator=(const BinaryTree<Entry> &original);    // Operator =
        virtual ~BinaryTree();  // Destructor
        // Traverse methods:
        template<typename Function>
        void preorder(Function visit);  // Preorder traversal
        template<typename Function>
        void inorder(Function visit);   // Inorder traversal
        template<typename Function>
        void postorder(Function visit); // Postorder traversal
        template<typename Function>
        void levelOrder(Function visit);    // Level traversal
        // Property getter methods:
        bool empty() const; // Judge whether the binary tree is empty or not
        int height() const; // The height of the tree
        int width() const;  // The width of the tree
        int count(int degree) const;    // The number of nodes with degree 0, 1 or 2
        // Create and clear methods:
        void clear();   // Clear the tree
        void createByPreorderInorder(const std::vector<Entry> &preorderContainer,
                                     const std::vector<Entry> &inorderContainer);  // Create tree by preorder and inorder
        void createByInorderPostorder(const std::vector<Entry> &inorderContainer,
                                      const std::vector<Entry> &postorderContainer);  // Create tree by inorder and postorder
    protected:
        BinaryNode<Entry> *root;    // root node

        // Functiontions called recursively:
        template<typename Function>
        static void recursivePreorder(BinaryNode<Entry> *subRoot, Function visit);

        template<typename Function>
        static void recursiveInorder(BinaryNode<Entry> *subRoot, Function visit);

        template<typename Function>
        static void recursivePostorder(BinaryNode<Entry> *subRoot, Function visit);

        static int recursiveHeight(BinaryNode<Entry> *subRoot);

        static int recursiveDegreeCount(BinaryNode<Entry> *subRoot, int degree);

        static BinaryNode<Entry> *recursiveCopy(BinaryNode<Entry> *subRoot);

        static void recursiveClear(BinaryNode<Entry> *&subRoot);

        static void recursiveCreateByPreorderInorder(BinaryNode<Entry> *&subRoot,
                                                     const std::vector<Entry> &preorderContainer,
                                                     const std::vector<Entry> &inorderContainer);

        static void recursiveCreateByInorderPostorder(BinaryNode<Entry> *&subRoot,
                                                      const std::vector<Entry> &inorderContainer,
                                                      const std::vector<Entry> &postorderContainer);
    };

}

/**
 * BinaryTree<> default constructor
 * @post An empty binary tree has been created.
 */
template<typename Entry>
tree::BinaryTree<Entry>::BinaryTree() : root(nullptr) {}

/**
 * preorder method
 * @post The tree has been been traversed in preorder sequence.
 * @uses The function recursivePreorder
 * @param visit Function object
 */
template<typename Entry>
template<typename Function>
void tree::BinaryTree<Entry>::preorder(Function visit) {
    recursivePreorder(root, visit);
}

/**
 * recursivePreorder function
 * @post The subtree rooted at subRoot has been been traversed in preorder sequence.
 * @uses The function recursivePreorder recursively
 * @param subRoot The root node of tree or subtree
 * @param visit Function object
 */
template<typename Entry>
template<typename Function>
void tree::BinaryTree<Entry>::recursivePreorder(BinaryNode<Entry> *subRoot, Function visit) {
    if (subRoot != nullptr) {
        (*visit)(subRoot->data);
        recursivePreorder(subRoot->left, visit);
        recursivePreorder(subRoot->right, visit);
    }
}

/**
 * inorder method
 * @post The tree has been been traversed in inorder sequence.
 * @uses The function recursiveInorder
 * @param visit Function object
 */
template<typename Entry>
template<typename Function>
void tree::BinaryTree<Entry>::inorder(Function visit) {
    recursiveInorder(root, visit);
}

/**
 * recursiveInorder function
 * @post The subtree rooted at subRoot has been been traversed in inorder sequence.
 * @uses The function recursiveInorder recursively
 * @param subRoot The root node of tree or subtree
 * @param visit Function object
 */
template<typename Entry>
template<typename Function>
void tree::BinaryTree<Entry>::recursiveInorder(BinaryNode<Entry> *subRoot, Function visit) {
    if (subRoot != nullptr) {
        recursiveInorder(subRoot->left, visit);
        (*visit)(subRoot->data);
        recursiveInorder(subRoot->right, visit);
    }
}

/**
 * postorder method
 * @post The tree has been been traversed in postorder sequence.
 * @uses The function recursivePostorder
 * @param visit Function object
 */
template<typename Entry>
template<typename Function>
void tree::BinaryTree<Entry>::postorder(Function visit) {
    recursivePostorder(root, visit);
}

/**
 * recursivePostorder function
 * @post The subtree rooted at subRoot has been been traversed in postorder sequence.
 * @uses The function recursivePostorder recursively
 * @param subRoot The root node of tree or subtree
 * @param visit Function object
 */
template<typename Entry>
template<typename Function>
void tree::BinaryTree<Entry>::recursivePostorder(BinaryNode<Entry> *subRoot, Function visit) {
    if (subRoot != nullptr) {
        recursivePostorder(subRoot->left, visit);
        recursivePostorder(subRoot->right, visit);
        (*visit)(subRoot->data);
    }
}

/**
 * levelOrder method
 * @post The tree has been been traversed in level order sequence.
 * @uses std::queue object as a queue
 * @param visit Function object
 */
template<typename Entry>
template<typename Function>
void tree::BinaryTree<Entry>::levelOrder(Function visit) {
    if (root == nullptr) { return; }
    std::queue<BinaryNode<Entry> *> nodeQueue;
    nodeQueue.push(root);
    while (!nodeQueue.empty()) {
        BinaryNode<Entry> *p = nodeQueue.front();
        (*visit)(p->data);
        // Push left child and right child into the node queue.
        if (p->left != nullptr) { nodeQueue.push(p->left); }
        if (p->right != nullptr) { nodeQueue.push(p->right); }
        nodeQueue.pop();
    } // end while-loop
}

/**
 * empty method
 * @return A result of true is returned if the binary tree is empty.
 *         Otherwise, false is returned.
 */
template<typename Entry>
bool tree::BinaryTree<Entry>::empty() const {
    return root == nullptr;
}

/**
 * height method
 * @uses The function recursiveHeight
 * @return The height of the tree is returned.
 */
template<typename Entry>
int tree::BinaryTree<Entry>::height() const {
    return recursiveHeight(root);
}

/**
 * recursiveHeight function
 * @uses The function recursiveHeight recursively, The function std::max to calculate the max height
 * @param subRoot The root node of tree or subtree
 * @return The height of the subtree rooted at subRoot is returned.
 */
template<typename Entry>
int tree::BinaryTree<Entry>::recursiveHeight(BinaryNode<Entry> *subRoot) {
    if (subRoot == nullptr) { return 0; }   // Empty tree
    // The height of tree at subRoot = max{left child height, right child height} + 1(self)
    return std::max(recursiveHeight(subRoot->left), recursiveHeight(subRoot->right)) + 1;
}

/**
 * width method
 * @uses std::queue object as a queue
 * @return The number of nodes in the level with the most nodes.
 */
template<typename Entry>
int tree::BinaryTree<Entry>::width() const {
    std::queue<BinaryNode<Entry> *> nodeQueue;  // The nodes in the queue is the same level
    int maxWidth = 0;
    if (root != nullptr) { nodeQueue.push(root); }
    while (!nodeQueue.empty()) {
        // Calculate the width in this level
        int levelWidth = nodeQueue.size();
        maxWidth = maxWidth < levelWidth ? levelWidth : maxWidth;
        for (int i = 0; i < levelWidth; ++i) {
            BinaryNode<Entry> *p = nodeQueue.front();
            // Push left child and right child into the node queue.
            if (p->left != nullptr) { nodeQueue.push(p->left); }
            if (p->right != nullptr) { nodeQueue.push(p->right); }
            nodeQueue.pop();
        } // end for-loop
    } // end while-loop
    return maxWidth;
}

/**
 * count method
 * @uses The function recursiveDegreeCount
 * @param degree The degree of node
 * @throw std::invalid_argument if invalid degree is given.
 * @return The number of nodes with degree
 */
template<typename Entry>
int tree::BinaryTree<Entry>::count(int degree) const {
    return recursiveDegreeCount(root, degree);
}

/**
 * recursiveDegreeCount function
 * @uses The function recursiveDegreeCount recursively
 * @param subRoot The root node of tree or subtree
 * @param degree The degree of node
 * @throw std::invalid_argument if invalid degree is given.
 * @return The number of nodes in tree subRoot with degree
 */
template<typename Entry>
int tree::BinaryTree<Entry>::recursiveDegreeCount(BinaryNode<Entry> *subRoot, int degree) {
    if (degree < 0 || degree > 2) {
        throw std::invalid_argument{"degree out of its range"};
    }
    if (subRoot == nullptr) { return 0; } // Empty tree
    int child = 0;
    if (subRoot->left != nullptr) { child++; }
    if (subRoot->right != nullptr) { child++; }
    if (child == degree) {  // Find the same degree node
        return 1 + recursiveDegreeCount(subRoot->left, degree) + recursiveDegreeCount(subRoot->right, degree);
    }
    return recursiveDegreeCount(subRoot->left, degree) + recursiveDegreeCount(subRoot->right, degree);
}

/**
 * BinaryTree<> copy constructor
 * @uses The function recursiveCopy
 * @param original The new tree to copy
 */
template<typename Entry>
tree::BinaryTree<Entry>::BinaryTree(const BinaryTree<Entry> &original) {
    root = recursiveCopy(original.root);
}

/**
 * BinaryTree<> operator=
 * @uses The function recursiveCopy, recursiveClear
 * @param original The new tree to assign
 */
template<typename Entry>
tree::BinaryTree<Entry> &tree::BinaryTree<Entry>::operator=(const BinaryTree<Entry> &original) {
    if (root != nullptr) { recursiveClear(root); }  // delete the old tree
    root = recursiveCopy(original.root);    // copy the new tree
    return *this;
}

/**
 * recursiveCopy function
 * @uses The function recursiveCopy recursively
 * @param subRoot The root node of tree or subtree
 * @return The subtree rooted at subRoot is copied, and a pointer to the root of the new copy is returned.
 */
template<typename Entry>
tree::BinaryNode<Entry> *tree::BinaryTree<Entry>::recursiveCopy(BinaryNode<Entry> *subRoot) {
    if (subRoot == nullptr) return nullptr;
    auto *newRoot = new BinaryNode<Entry>(subRoot->data);
    newRoot->left = recursiveCopy(subRoot->left);
    newRoot->right = recursiveCopy(subRoot->right);
    return newRoot;
}

/**
 * clear method
 * @uses The function recursiveClear
 */
template<typename Entry>
void tree::BinaryTree<Entry>::clear() {
    recursiveClear(root);
}

/**
 * BinaryTree<> destructor
 * @uses The function recursiveClear
 */
template<typename Entry>
tree::BinaryTree<Entry>::~BinaryTree() {
    recursiveClear(root);
}

/**
 * recursiveClear function
 * @post Clear the subtree rooted at subRoot.
 * @uses The function recursiveClear recursively
 * @param subRoot The root node of tree or subtree (Pointer reference)
 */
template<typename Entry>
void tree::BinaryTree<Entry>::recursiveClear(BinaryNode<Entry> *&subRoot) {
    if (subRoot != nullptr) {
        recursiveClear(subRoot->left);
        recursiveClear(subRoot->right);
        delete subRoot;
        subRoot = nullptr;
    }
}

/**
 * createByPreorderInorder method
 * @post Create the tree using preorder sequence and inorder sequence.
 * @uses The function recursiveCreateByPreorderInorder, type std::vector<>
 * @param preorderContainer perOrder sequence
 * @param inorderContainer inorder sequence
 * @throw std::invalid_argument if invalid Container is given. Then this tree will be empty.
 */
template<typename Entry>
void tree::BinaryTree<Entry>::createByPreorderInorder(const std::vector<Entry> &preorderContainer,
                                                      const std::vector<Entry> &inorderContainer) {
    recursiveCreateByPreorderInorder(root, preorderContainer, inorderContainer);
}

/**
 * recursiveCreateByPreorderInorder function
 * @post Create the tree using perOrder sequence and inorder sequence.
 * @uses The function recursiveCreateByPreorderInorder recursively, type std::vector<>,
 *       the function std::find to find root node position in inorder sequence
 * @param subRoot The root node of tree or subtree (Pointer reference)
 * @param preorderContainer perOrder sequence
 * @param inorderContainer inorder sequence
 * @throw std::invalid_argument if invalid Container is given. Then this tree will be empty.
 */
template<typename Entry>
void
tree::BinaryTree<Entry>::recursiveCreateByPreorderInorder(BinaryNode<Entry> *&subRoot,
                                                          const std::vector<Entry> &preorderContainer,
                                                          const std::vector<Entry> &inorderContainer) {
    if (subRoot != nullptr) { recursiveClear(subRoot); }   // Clear the tree.
    if (preorderContainer.size() == 0) { return; }  // Empty tree
    if (preorderContainer.size() != inorderContainer.size()) {
        throw std::invalid_argument{"the size of containers are not equal"};
    }
    const Entry rootElem = preorderContainer.front();   // root node
    // Find root node position in inorder sequence and the length of left sequence.
    auto inorderRootPtr = find(inorderContainer.begin(), inorderContainer.end(), rootElem);
    if (inorderRootPtr == inorderContainer.end()) {
        throw std::invalid_argument{"root node not found in inorder container"};
    }
    std::size_t leftLength = inorderRootPtr - inorderContainer.begin();
    // Split preorder and inorder sequence by root node.
    const std::vector<Entry> inorderLeft(inorderContainer.begin(),
                                         inorderContainer.begin() + leftLength);
    const std::vector<Entry> inorderRight(inorderContainer.begin() + leftLength + 1,
                                          inorderContainer.end());
    const std::vector<Entry> preorderLeft(preorderContainer.begin() + 1,
                                          preorderContainer.begin() + leftLength + 1);
    const std::vector<Entry> preorderRight(preorderContainer.begin() + leftLength + 1,
                                           preorderContainer.end());
    // Recursively create left and right tree.
    subRoot = new BinaryNode<Entry>(rootElem);
    recursiveCreateByPreorderInorder(subRoot->left, preorderLeft, inorderLeft);
    recursiveCreateByPreorderInorder(subRoot->right, preorderRight, inorderRight);
}

/**
 * createByInorderPostorder method
 * @post Create the tree using inorder sequence and postorder sequence.
 * @uses The function recursiveCreateByInorderPostorder, type std::vector<>
 * @param inorderContainer inorder sequence
 * @param postorderContainer postorder sequence
 * @throw std::invalid_argument if invalid Container is given. Then this tree will be empty.
 */
template<typename Entry>
void tree::BinaryTree<Entry>::createByInorderPostorder(const std::vector<Entry> &inorderContainer,
                                                       const std::vector<Entry> &postorderContainer) {
    recursiveCreateByInorderPostorder(root, inorderContainer, postorderContainer);
}

/**
 * recursiveCreateByInorderPostorder function
 * @post Create the tree using inorder sequence and postorder sequence.
 * @uses The function recursiveCreateByInorderPostorder recursively, type std::vector<>,
 *       the function std::find to find root node position in inorder sequence
 * @param subRoot The root node of tree or subtree (Pointer reference)
 * @param inorderContainer inorder sequence
 * @param postorderContainer postorder sequence
 * @throw std::invalid_argument if invalid Container is given. Then this tree will be empty.
 */
template<typename Entry>
void
tree::BinaryTree<Entry>::recursiveCreateByInorderPostorder(BinaryNode<Entry> *&subRoot,
                                                           const std::vector<Entry> &inorderContainer,
                                                           const std::vector<Entry> &postorderContainer) {
    if (subRoot != nullptr) { recursiveClear(subRoot); }   // Clear the tree.
    if (inorderContainer.size() == 0) { return; }   // Empty tree
    if (postorderContainer.size() != inorderContainer.size()) {
        throw std::invalid_argument{"the size of containers are not equal"};
    }
    const Entry rootElem = postorderContainer.back();   // root node
    // Find root node position in inorder sequence and the length of left sequence.
    auto inorderRootPtr = find(inorderContainer.begin(), inorderContainer.end(), rootElem);
    if (inorderRootPtr == inorderContainer.end()) {
        throw std::invalid_argument{"root node not found in inorder container"};
    }
    std::size_t leftLength = inorderRootPtr - inorderContainer.begin();
    // Split postorder and inorder sequence by root node.
    const std::vector<Entry> inorderLeft(inorderContainer.begin(),
                                         inorderContainer.begin() + leftLength);
    const std::vector<Entry> inorderRight(inorderContainer.begin() + leftLength + 1,
                                          inorderContainer.end());
    const std::vector<Entry> postorderLeft(postorderContainer.begin(),
                                           postorderContainer.begin() + leftLength);
    const std::vector<Entry> postorderRight(postorderContainer.begin() + leftLength,
                                            postorderContainer.end() - 1);
    // Recursively create left and right tree.
    subRoot = new BinaryNode<Entry>(rootElem);
    recursiveCreateByInorderPostorder(subRoot->left, inorderLeft, postorderLeft);
    recursiveCreateByInorderPostorder(subRoot->right, inorderRight, postorderRight);
}


#endif //TREE_BINARY_TREE_HPP
