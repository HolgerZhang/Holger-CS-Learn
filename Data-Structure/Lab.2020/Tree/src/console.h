#ifndef TREE_CONSOLE_H
#define TREE_CONSOLE_H

#include "tree/binary_tree.hpp"
#include "tree/binary_search_tree.hpp"
#include "menu/menu.h"

/**
 * Console Class
 * @details The class of console sessions.
 */
class Console {
public:
    Console() : tree(nullptr), type(menu::TreeType::None) { onStart(); }  // Constructor
    ~Console() { onDestroy(); }  // Destructor
    void initialize();  // Initialize the sessions before executing.
    int exec(); // Execute the session.
private:
    tree::BinaryTree<char> *tree;  // The pointer of tree instance.
    menu::TreeType type;   // The type of the tree instance.

    // Console executive functions:
    void onStart(); // Switch user's choice to instantiate the class and call create function.
    // Called when console sessions are destructed.
    void onDestroy() {
        if (tree != nullptr) { delete tree; }
        tree = nullptr;
    }

    void createBinaryTree(); // Guide users to initialize BinaryTree instance.
    void createBSTree(); // Guide users to initialize BinarySearchTree instance.
    int funcProcess(menu::TreeFunc choice); // Deal with the methods that BinaryTree and BinarySearchTree have.

    // Console states controlling functions:
    // Clear the screen.
    static void clear() { std::cout << "\033[1H\033[2J" << std::flush; }

    // Pause and wait for user
    static void pause() {
        std::cout << "Press 'Enter' to continue..." << std::flush;
        std::string str;
        std::getline(std::cin, str);
    }

    static char getchar(const std::string &info = "Input"); // Get a character from standard input.
};

#endif //TREE_CONSOLE_H
