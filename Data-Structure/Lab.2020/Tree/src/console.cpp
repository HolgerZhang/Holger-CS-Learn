#include "console.h"

/**
 * initialize method
 * @pre onStart method called in advance.
 * @post Initialize the sessions before executing.
 */
void Console::initialize() {
    std::cout << "Now initialize the tree." << std::endl;
    switch (type) {
        case menu::TreeType::None:
            throw std::runtime_error{"'onStart' method should be called in advance."};
        case menu::TreeType::BinaryTree:
            createBinaryTree();
            break;
        case menu::TreeType::BinarySearchTree:
            createBSTree();
            break;
    }
    pause();
}

/**
 * exec method
 * @pre initialize method and onStart method called in advance.
 * @post Execute the program.
 * @return exit code 0
 */
int Console::exec() {
    // Check prior conditions
    if (type == menu::TreeType::None) {
        throw std::runtime_error{"'onStart' method should be called in advance."};
    } else if (tree == nullptr) {
        throw std::runtime_error{"'initialize' method should be called in advance."};
    }
    for (;;) {    // Main Loop
        clear();
        std::cout << menu::PUBLIC_FUNC_MENU
                  << (type == menu::TreeType::BinarySearchTree ? menu::BST_ONLY_FUNC_MENU : "")
                  << menu::PUBLIC_CONTROL_MENU << std::endl;
        if (funcProcess((menu::TreeFunc) menu::getSelectedNumber()) == 0) {
            return 0;
        }
    } // end Main Loop
}

/**
 * funcProcess function
 * @post Deal with the methods that BinaryTree and BinarySearchTree have.
 * @param choice user's choice number
 * @param choice
 * @return exit code 0 to tell exec return 0, else 1 to continue
 */
int Console::funcProcess(menu::TreeFunc choice) {
    char elem;
    switch (choice) {   // Process user's choice
        case menu::TreeFunc::preorder: {    // Preorder traversal
            std::cout << "The preorder sequence of tree is: ";
            tree->preorder(menu::putChar);
            std::cout << std::endl;
            pause();
            break;
        }
        case menu::TreeFunc::inorder: { // Inorder traversal
            std::cout << "The inorder sequence of tree is: ";
            tree->inorder(menu::putChar);
            std::cout << std::endl;
            pause();
            break;
        }
        case menu::TreeFunc::postorder: {   // Postorder traversal
            std::cout << "The postorder sequence of tree is: ";
            tree->postorder(menu::putChar);
            std::cout << std::endl;
            pause();
            break;
        }
        case menu::TreeFunc::levelOrder: {  // Level traversal
            std::cout << "The level order sequence of tree is: ";
            tree->levelOrder(menu::putChar);
            std::cout << std::endl;
            pause();
            break;
        }
        case menu::TreeFunc::height: {  // The height of the tree
            std::cout << "The height of tree is: " << tree->height();
            std::cout << std::endl;
            pause();
            break;
        }
        case menu::TreeFunc::width: {   // The width of the tree
            std::cout << "The width of tree is: " << tree->width();
            std::cout << std::endl;
            pause();
            break;
        }
        case menu::TreeFunc::degree: {  // The number of nodes with degree n
            int deg, count;
            deg = menu::getSelectedNumber("Please input the degree");
            try {
                count = tree->count(deg);
                std::cout << "There are " << count << " nodes with degree " << deg << " in the tree" << std::endl;
            } catch (std::invalid_argument &error) {
                std::cout << "Catch an error: " << error.what() << ". Try again." << std::endl;
            } // end try-catch
            pause();
            break;
        }
        case menu::TreeFunc::insert_elem: { // insert an element
            if (type != menu::TreeType::BinarySearchTree) {
                std::cout << "Undefined command." << std::endl;
                pause();
                break;
            }
            elem = getchar("Please enter the element to be inserted");
            std::cout << "The element '" << elem
                      << (((tree::BinarySearchTree<char> *) tree)->insert(elem) ? "' is inserted successfully."
                                                                                : "' is already in the tree.")
                      << std::endl;
            pause();
            break;
        }
        case menu::TreeFunc::remove_elem: { // remove an element
            if (type != menu::TreeType::BinarySearchTree) {
                std::cout << "Undefined command." << std::endl;
                pause();
                break;
            }
            elem = getchar("Please enter the element to be removed");
            std::cout << "The element '" << elem
                      << (((tree::BinarySearchTree<char> *) tree)->remove(elem) ? "' is removed successfully."
                                                                                : "' is NOT in the tree.")
                      << std::endl;
            pause();
            break;
        }
        case menu::TreeFunc::search_elem: { // search an element
            if (type != menu::TreeType::BinarySearchTree) {
                std::cout << "Undefined command." << std::endl;
                pause();
                break;
            }
            elem = getchar("Please enter the element to be searched");
            std::cout << "The element '" << elem
                      << (((tree::BinarySearchTree<char> *) tree)->search(elem) ? "' is found in the tree."
                                                                                : "' is NOT found in the tree.")
                      << std::endl;
            pause();
            break;
        }
        case menu::TreeFunc::reset: {   // Clear the tree
            tree->clear();
            initialize();
            break;
        }
        case menu::TreeFunc::back: {    // Return to main menu
            onDestroy();
            onStart();
            initialize();
            break;
        }
        case menu::TreeFunc::exit: { // Exit the program
            onDestroy();
            return 0;
        }
        default:
            std::cout << "Undefined command." << std::endl;
            pause();
    } // end switch
    return 1;
}

/**
 * onStart function
 * @pre Called when console sessions are created.
 * @post Switch user's choice to instantiate the class and call create function.
 */
void Console::onStart() {
    clear();
    std::cout << menu::WELCOME << std::endl;
    std::cout << menu::TREE_TYPE_MENU << std::endl;
    bool loop = true;
    while (loop) {   // Process user's choice
        menu::SelectedNumber choice = menu::getSelectedNumber();
        if ((menu::TreeFunc) choice == menu::TreeFunc::exit) {  // exit the program
            std::exit(0);
        }
        switch ((menu::TreeType) choice) {
            case menu::TreeType::BinaryTree: {  // Binary Tree
                tree = new tree::BinaryTree<char>;
                loop = false;
                type = menu::TreeType::BinaryTree;
                break;
            }
            case menu::TreeType::BinarySearchTree: {  // Binary Search Tree
                tree = new tree::BinarySearchTree<char>;
                loop = false;
                type = menu::TreeType::BinarySearchTree;
                break;
            }
            default:    // Check the legality of Selected Number
                std::cout << "Undefined command." << std::endl;
        } // end switch
    } // end loop
}

/**
 * createBinaryTree function
 * @post Guide users to initialize BinaryTree instance.
 */
void Console::createBinaryTree() {
    std::cout << menu::BINARY_TREE_CREATION_MENU << std::endl;
    menu::BinaryTreeCreation choice;
    for (;;) {  // Get user choice
        choice = (menu::BinaryTreeCreation) menu::getSelectedNumber();
        // Check the legality of Selected Number
        if (choice == menu::BinaryTreeCreation::preorder_inorder ||
            choice == menu::BinaryTreeCreation::inorder_postorder) { break; }
        std::cout << "Undefined command." << std::endl;
    } // end loop
    for (;;) {  // Creat tree
        bool endloop = true;
        std::string inorderStr, anotherStr;
        std::cout << "Please input the inorder sequence: " << std::flush;
        std::getline(std::cin, inorderStr);
        std::cout << "Please input another sequence: " << std::flush;
        std::getline(std::cin, anotherStr);
        std::vector<char> inorderSequence(inorderStr.begin(), inorderStr.end());
        std::vector<char> anotherSequence(anotherStr.begin(), anotherStr.end());
        try {
            if (choice == menu::BinaryTreeCreation::preorder_inorder) {
                tree->createByPreorderInorder(anotherSequence, inorderSequence);
            } else { tree->createByInorderPostorder(inorderSequence, anotherSequence); }
        } catch (std::invalid_argument &error) {
            std::cout << "Catch an error when creating tree: " << error.what() << ". Try again." << std::endl;
            endloop = false;
        } // end try-catch
        if (endloop) { break; }
    } // end loop
}

/**
 * createBSTree function
 * @post  Guide users to initialize BinarySearchTree instance.
 */
void Console::createBSTree() {
    std::string str;
    std::cout << "Please input the sequence of elements: " << std::flush;
    std::getline(std::cin, str);
    // Create tree
    std::vector<char> sequence(str.begin(), str.end());
    ((tree::BinarySearchTree<char> *) tree)->create(sequence);
}

/**
 * Get a character from standard input.
 * @param info prompt information
 * @return The character.
 */
char Console::getchar(const std::string &info) {
    std::string line;
    for (;;) {
        std::cout << info << ": " << std::flush;
        std::getline(std::cin, line);
        if (!line.empty()) { break; }
    }
    return line[0];
}
