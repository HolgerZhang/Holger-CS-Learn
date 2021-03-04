#include "menu.h"

// Welcome string.
const char menu::WELCOME[] = "Welcome to the Binary Tree Demo Program!\n"
                             "Author: Zhang Hao  Time: 2020-11-25.";
// Public function choice menu.
const char menu::PUBLIC_FUNC_MENU[] = "\n"
                                      "  #########################################  \n"
                                      "            The Functions of Tree            \n"
                                      "  #########################################  \n"
                                      "     [1] Preorder traversal                  \n"
                                      "     [2] Inorder traversal                   \n"
                                      "     [3] Postorder traversal                 \n"
                                      "     [4] Level traversal                     \n"
                                      "     [5] The height of the tree              \n"
                                      "     [6] The width of the tree               \n"
                                      "     [7] The number of nodes with degree n   \n";
// BST function (only) choice menu.
const char menu::BST_ONLY_FUNC_MENU[] = "   --- --- --- --- --- --- --- --- --- ---   \n"
                                        "     [8] insert an element                   \n"
                                        "     [9] remove an element                   \n"
                                        "    [10] search an element                   \n";
// Public control choice menu.
const char menu::PUBLIC_CONTROL_MENU[] = "   --- --- --- --- --- --- --- --- --- ---   \n"
                                         "    [11] RESET: clear the tree               \n"
                                         "    [12] BACK: return to main menu           \n"
                                         "    [13] EXIT: exit the program              \n"
                                         "  #########################################  \n";
// Choice tree type menu.
const char menu::TREE_TYPE_MENU[] = "\n"
                                    "  ####################################  \n"
                                    "            The Type of Tree            \n"
                                    "  ####################################  \n"
                                    "     [1] Binary Tree                    \n"
                                    "     [2] Binary Search Tree             \n"
                                    "    [13] EXIT: exit the program         \n"
                                    "  ####################################  \n";
// Create method choice of BinaryTree menu.
const char menu::BINARY_TREE_CREATION_MENU[] = "\n"
                                               "> Choose your creation type:                       \n"
                                               "> [1] Using preorder sequence and inorder sequence \n"
                                               "> [2] Using inorder sequence and postorder sequence\n";

/**
 * getSelectedNumber function
 * @post Get an integer as selected number from standard input.
 * @param info prompt information
 * @return The integer.
 */
menu::SelectedNumber menu::getSelectedNumber(const std::string &info) {
    std::string cmd;
    char *p;
    bool loop = true;
    while (loop) {
        std::cout << info << ": " << std::flush;
        std::getline(std::cin, cmd);
        if (cmd.empty()) { continue; }
        loop = false;
        for (char ch : cmd) {   // Check for legal string
            if (!isdigit(ch)) {
                loop = true;
                std::cout << "Invalid command." << std::endl;
                break;
            } // end if
        } // end check loop
    } // end loop
    return (menu::SelectedNumber) strtol(cmd.c_str(), &p, 10);
}

/**
 * putChar function
 * @post Print an character into standard output.
 * @param ch the character
 */
void menu::putChar(char &ch) { std::cout << ch << std::flush; }
