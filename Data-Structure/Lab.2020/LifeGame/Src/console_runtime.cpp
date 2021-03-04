//
// Created by holger on 2020/10/31.
//

#include "console_runtime.h"

char console_runtime::wait_user(const string &info) {
    string line;
    while (line.empty()) {
        if (cin.eof()) {
            exit(0);
        }
        cout << "Game-[" + info + "]$ ";
        getline(cin, line);
    }
    return line[0];
}

void
console_runtime::show_error(exception &error, const string &state, const string &file, bool terminal, int exit_code) {
    cout << CONSOLE_RED << "Error [" << typeid(error).name() << "] In '" << file << "'" << endl
         << "  " << state << ": " << error.what() << CONSOLE_RESET << endl;
    if (terminal) { exit(exit_code); }
}

void console_runtime::execute(Life &life, char option) {
    switch (option) {
        case 's':
        case 'S':
            cout << "Now the configuration is: " << endl;
            life.show();
            break;
        case 'n':
        case 'N':
            life.update();
            cout << "Configuration is updated to next status." << endl;
            break;
        case 'q':
        case 'Q':
            cout << "Game process finished." << endl;
            exit(0);
        case '?':
            cout << MENU << endl;
            break;
        default:
            throw std::runtime_error{"Invalid command"};
    }
}