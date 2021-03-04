#include <iostream>
#include "solution.hpp"

using namespace std;

int main() {
    // a sample example
    int student1Cards[5] = {2, 3, 5, 6, 1};
    int student2Cards[5] = {1, 5, 4, 2, 9};
    Queue<int> student1, student2;
    Stack<int> desk;
    initializeQueue<int>(student1, student1Cards, 5);
    initializeQueue<int>(student2, student2Cards, 5);
    switch (fishing_game::solution<10>(student1, student2, desk)) {
        case fishing_game::state::student1_win:
            cout << "Student1 win the game.\n";
            break;
        case fishing_game::state::student2_win:
            cout << "Student2 win the game.\n";
            break;
    }
    return 0;
}
