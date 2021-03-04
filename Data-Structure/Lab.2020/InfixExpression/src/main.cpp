#include <iostream>
#include <fstream>
#include "util/infix_expression.h"

#define CONSOLE_RED "\033[31m"
#define CONSOLE_RESET "\033[0m"

using namespace std;

const static string INFO = "Infix Expression Calculator (Oct. 06 2020) By Holger Zhang\n"
                           "Type \"exit\" to exit the shell.\n"
                           "  < '~' means minus '-' >  \n\n";

int exec() {
    string option;
    cout << "* Show the changing process of the stack and the expression? [Y/n] " << flush;
    while (option.empty()) { getline(cin, option); }
    InfixExpression::showDetail(option[0] == 'y' || option[0] == 'Y');
    string line;
    while (true) {
        cout << flush;
        // Read infix expression from standard input.
        cout << ">>> " << flush;
        getline(cin, line);
        if (cin.eof() || line == "exit") {
            return 0;
        } else if (line.empty()) {
            continue;
        }
        try {
            cout << InfixExpression(line).calculate() << endl;
        } catch (std::runtime_error &e) {
            cout << CONSOLE_RED << "Unexpected line in <stdin> : " << line << endl
                 << e.what() << CONSOLE_RESET << endl;
        }
    }
}

int exec_file(const string &file) {
    ifstream in(file);
    ofstream out(file + "_out.txt");
    if ((!in.is_open()) || (!out.is_open())) {
        cerr << "invalid file path." << endl;
        return -1;
    }
    string line;
    while (!in.eof()) {
        // Read infix expression from file.
        getline(in, line);
        if (line.empty()) {
            continue;
        }
        try {
            out << InfixExpression(line).calculate() << endl;
        } catch (std::runtime_error &e) {
            cerr << "Unexpected line in \"" + file + "\" : " << line << endl
                 << e.what() << endl;
            in.close();
            out.close();
            return -2;
        }
    }
    in.close();
    out.close();
    return 0;
}

int main(int argc, const char **argv) {
    if (argc >= 2) {
        return exec_file(argv[argc - 1]);
    }
    cout << INFO;
    return exec();
}
