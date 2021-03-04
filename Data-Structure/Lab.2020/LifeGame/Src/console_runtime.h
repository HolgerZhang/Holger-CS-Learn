//
// Created by holger on 2020/10/31.
//

#ifndef LIFE_GAME_UTIL_H
#define LIFE_GAME_UTIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "life.h"

using namespace std;

namespace console_runtime {
    constexpr char CONSOLE_RED[] = "\033[31m";
    constexpr char CONSOLE_RESET[] = "\033[0m";
    constexpr char MENU[] = "\n"
                            "\t-----------------------------\t\n"
                            "\t| -*-*-*- Life Game -*-*-*- |\t\n"
                            "\t|========= M E N U =========|\t\n"
                            "\t|[s] Show the configuration |\t\n"
                            "\t|[n] Next status            |\t\n"
                            "\t|[q] Quit the game          |\t\n"
                            "\t|[?] Show this menu again   |\t\n"
                            "\t-----------------------------\t\n";

    // Waiting for user input option
    char wait_user(const string &info = "wait for input");

    // After capturing the error, output the error message
    void show_error(exception &error,
                    const string &state,
                    const string &file = "<stdin>",
                    bool terminal = false,
                    int exit_code = 0);

    // Call the corresponding method of class Life according to the option
    void execute(Life &life, char option);
}

#endif //LIFE_GAME_UTIL_H
