// File: solution.hpp
// Created by holger on 2020/10/15.
// The solution functions

#ifndef CAT_FISHING_SOLUTION
#define CAT_FISHING_SOLUTION

#include <iostream>
#include "util/container/sequence_stack.hpp"
#include "util/container/linked_queue.hpp"

namespace fishing_game {

    enum class state {
        student1_win, student2_win
    };

    inline void showState(const Queue<int> &stu1, const Queue<int> &stu2, const Stack<int> &desk) {
        std::cout << "The cards on the desk: ";
        desk.print();
        std::cout << std::endl << "The cards in student1's hand: ";
        stu1.print();
        std::cout << std::endl << "The cards in student2's hand: ";
        stu2.print();
        std::cout << std::endl;
    }

    void playCard(Queue<int> &student, Stack<int> &desk, int counter[]) {
        int now = student.front();
        desk.push(student.pop());
        counter[now]++;
        if (counter[now] == 2) {
            // Move cards to stu's hand
            Stack<int> temp;
            do {
                counter[desk.top()]--;
                temp.push(desk.pop());
            } while (desk.top() != now);
            counter[desk.top()]--;
            temp.push(desk.pop());
            while (!temp.empty()) {
                student.push(temp.pop());
            }
        }
    }

    template<int cardsNumberUpperBound>
    state solution(Queue<int> &stu1, Queue<int> &stu2, Stack<int> &desk) {
        int counter[cardsNumberUpperBound]{};   // Count the cards
        int count = 0;
        std::cout << "Student1: A and Student2: B are playing the card game called Cat Fishing.\n";
        showState(stu1, stu2, desk);
        for (;;) {
            std::cout << "|> Round #" << ++count << std::endl;
            playCard(stu1, desk, counter);
            if (stu1.empty()) {
                showState(stu1, stu2, desk);
                return state::student2_win;
            }
            playCard(stu2, desk, counter);
            if (stu2.empty()) {
                showState(stu1, stu2, desk);
                return state::student1_win;
            }
            showState(stu1, stu2, desk);
        }
    }

}


#endif  //CAT_FISHING_SOLUTION