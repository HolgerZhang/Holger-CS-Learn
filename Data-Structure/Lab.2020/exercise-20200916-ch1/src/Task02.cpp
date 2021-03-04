// Created by Zhang Hao on 2020/9/16.
// Coding: UTF-8
// File: Task02.cpp
// Task: Page.26, 4(2) Determines whether a string is a palindrome string.

#include <iostream>
#include <string>

/**
 * Determines whether a string is a palindrome string.
 * Time Complexity: O(n), n = the length of str
 * @param str   a std::string object which is provided.
 * @return      `true` if the string is a palindrome string,
 *              or `false` if the string is NOT a palindrome string.
 */
bool isPalindromeString(const std::string &str) {
    for (int i = 0; i < str.length() / 2; ++i) {
        if (str[i] != str[str.length() - 1 - i])
            return false;
    }
    return true;
}

int main() {
    std::string str1{"hello"}, str2{"abba"}, str3{"abcda"};
    std::cout << str1 << (isPalindromeString(str1) ? " is " : " isn't ") << "a palindrome string." << std::endl;
    std::cout << str2 << (isPalindromeString(str2) ? " is " : " isn't ") << "a palindrome string." << std::endl;
    std::cout << str3 << (isPalindromeString(str3) ? " is " : " isn't ") << "a palindrome string." << std::endl;
    return 0;
}