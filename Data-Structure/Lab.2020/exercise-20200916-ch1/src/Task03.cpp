// Created by Zhang Hao on 2020/9/16.
// Coding: UTF-8
// File: Task03.cpp
// Task: Page.26, 4(3)
//       Adjust the array of integer A[size] so that the left elements are odd, and the right elements are even.
//       Required Time Complexity: O(n)

#include <iostream>
#include <random>

/**
 * Adjust the array of integer A[size] so that the left elements are odd, and the right elements are even.
 * Time Complexity: O(n)
 * @param a     the array of integer A[]
 * @param size  the size of array A[]
 */
void adjustArray(int a[], unsigned size) {
    int leftPosition = 0, rightPosition = size - 1;
    while (leftPosition < rightPosition) {
        if (a[leftPosition] % 2 != 0) {     // left position element is odd -> pass.
            leftPosition++;
            continue;
        } else if (a[rightPosition] % 2 == 0) {    // right position element is even -> pass.
            rightPosition--;
            continue;
        }
        // left position element is even, right position element is odd -> swap.
        std::swap(a[leftPosition], a[rightPosition]);
        leftPosition++;
        rightPosition--;
    }
}

int main() {
    // Generate array randomly.
    std::random_device randomDevice;
    int array1[10], array2[13];
    for (int i = 0; i < 10; ++i) {
        array1[i] = (int) randomDevice() % 100;
    }
    for (int i = 0; i < 13; ++i) {
        array2[i] = (int) randomDevice() % 100;
    }

    // Show the random array.
    std::cout << "array1: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << array1[i] << '\t';
    }
    std::cout << std::endl;
    std::cout << "array2: ";
    for (int i = 0; i < 13; ++i) {
        std::cout << array2[i] << '\t';
    }
    std::cout << std::endl;

    // Adjust the array.
    adjustArray(array1, 10);
    adjustArray(array2, 13);

    // Show the random array.
    std::cout << "After adjustment:\n";
    std::cout << "array1: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << array1[i] << '\t';
    }
    std::cout << std::endl;
    std::cout << "array2: ";
    for (int i = 0; i < 13; ++i) {
        std::cout << array2[i] << '\t';
    }
    std::cout << std::endl;

    return 0;
}