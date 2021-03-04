#ifndef TREE_MENU_H
#define TREE_MENU_H

#include <iostream>
#include <string>
#include <cctype>

/**
 * menu namespace
 * @details strings of menu, selected numbers of each menu
 */
namespace menu {
    // String define:
    extern const char WELCOME[];            // Welcome string.
    extern const char PUBLIC_FUNC_MENU[];   // Public function choice menu.
    extern const char BST_ONLY_FUNC_MENU[]; // BST function (only) choice menu.
    extern const char PUBLIC_CONTROL_MENU[];// Public control choice menu.
    extern const char TREE_TYPE_MENU[];     // Choice tree type menu.
    extern const char BINARY_TREE_CREATION_MENU[];  // Create method choice of BinaryTree menu.

    // Type define:
    using SelectedNumber = int; // User's choice number.
    // Tree types.
    enum class TreeType {
        None = 0,
        BinaryTree = 1,
        BinarySearchTree = 2
    };
    // Tree functions.
    enum class TreeFunc {
        preorder = 1,
        inorder = 2,
        postorder = 3,
        levelOrder = 4,
        height = 5,
        width = 6,
        degree = 7,
        insert_elem = 8,
        remove_elem = 9,
        search_elem = 10,
        reset = 11,
        back = 12,
        exit = 13
    };
    // Create method choices of BinaryTree
    enum class BinaryTreeCreation {
        preorder_inorder = 1,
        inorder_postorder = 2
    };

    // Function define:
    // Get an integer as selected number from standard input.
    SelectedNumber getSelectedNumber(const std::string &info = "Your choice");

    // Print an character into standard output.
    void putChar(char &ch);
}

#endif //TREE_MENU_H
