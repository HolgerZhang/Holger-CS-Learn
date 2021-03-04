// Created by Zhang Hao on 2020/9/16.
// Coding: UTF-8
// File: Task04.cpp
// Task: Page.26, 4(4) The Problem of Dutch Flag.
//                     Rearrange an array consist of characters R, W, and B, all with R first, W second, amd B last.
//                     Required Time Complexity: O(n)

#include <iostream>

/**
 * Rearrange an array consist of characters R, W, and B, all with R first, W second, amd B last.
 * Time Complexity: O(n)
 * @param flagArray the array consist of characters R, W, and B.
 * @param size      the size of the array referenced.
 */
void sortFlag(char flagArray[], unsigned size) {
    int less = 0, more = size - 1, index = 0;
    while (index < more) {
        switch (flagArray[index]) {
            case 'R':   // `index` element is R -> swap with next `less` element.
                std::swap(flagArray[index++], flagArray[less++]);
                break;
            case 'W':   // `index` element is W -> pass.
                index++;
                break;
            case 'B':   // `index` element is B -> swap with previous `more` element.
                // BUT we do NOT know which type previous `more` element is,
                // so we need to make `index` still.
                std::swap(flagArray[index], flagArray[more--]);
                break;
        }
    }
}

int main() {
    char flag[10]{'B', 'W', 'R', 'W', 'R', 'B', 'W', 'B', 'W', 'R'};
    std::cout << "Before: ";
    for (int i = 0; i < 10; ++i)
        std::cout << flag[i] << ' ';    // show it
    std::cout << std::endl;

    sortFlag(flag, 10);
    std::cout << "After: ";
    for (int i = 0; i < 10; ++i)
        std::cout << flag[i] << ' ';    // show it
    std::cout << std::endl;

    return 0;
}