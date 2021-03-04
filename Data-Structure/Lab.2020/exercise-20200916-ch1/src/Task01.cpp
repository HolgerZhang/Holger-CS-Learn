// Created by Zhang Hao on 2020/9/16.
// Coding: UTF-8
// File: Task01.cpp
// Task: Page.26, 4(1) Find the max number and the secondary max number of the array of integer A[n].

#include <iostream>
#include <random>

/**
 * Find the max number and the secondary max number of the array of integer A[size].
 * Time Complexity: O(n)
 * @param A                 [in]    the array of integer A[]
 * @param size              [in]    the size of array A[]
 * @param maxNumber         [out]   the max number of the array A[size]
 * @param secondaryNumber   [out]   the secondary max number of the array A[size]
 */
void findMaxAndSecondaryNumber(const int A[], unsigned size, int &maxNumber, int &secondaryNumber) {
    maxNumber = A[0];
    for (int i = 1; i < size; ++i) {        // Find the max number of the array A[size].
        if (A[i] > maxNumber)
            maxNumber = A[i];
    }
    secondaryNumber = A[0];
    for (int i = 1; i < size; ++i) {
        if (A[i] < maxNumber && A[i] > secondaryNumber)   // Find the secondary max number of the array A[size].
            secondaryNumber = A[i];
    }
}

int main() {
    std::random_device randomDevice;
    int a[10];
    for (int i = 0; i < 10; ++i) {  // Generate array randomly.
        a[i] = (int) randomDevice() % 1000;
    }
    std::cout << "The array is: ";
    for (int i = 0; i < 10; ++i) {  // Show the random array.
        std::cout << a[i] << '\t';
    }
    std::cout << std::endl;

    int max, secondary;
    findMaxAndSecondaryNumber(a, 10, max, secondary);
    std::cout << "The max number is " << max << ", and the secondary max number is " << secondary << ".\n";

    return 0;
}