// File: calculator.cpp
// Created by holger on 2020/9/23.
// Simple long integer calculator for testing,
//   and a command line tool for batch processing a large number of long integer operations

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "util/integer.h"

using namespace std;

const static string INFO = "Big Integer Calculator (Sept. 30 2020) By Holger Zhang\n"
                           "Type \"exit\" to exit the shell.\n\n"
                           "[[NOTICE]] The operands and the operator must be divided by at least one blank.\n"
                           "<Sample Input>\n"
                           ">>> 6 * 7     # LeftOperand Operator RightOperand\n"
                           "42\n\n";

string eval(const string &line) {
    istringstream inStringStream(line);
    string leftOperand, rightOperand, result;
    char Operator;
    // Read operands and operator from string line.
    inStringStream >> leftOperand >> Operator >> rightOperand;
    BigInteger integer1(leftOperand), integer2(rightOperand);
    // Calculate
    switch (Operator) {
        case '+':
            result = integer1.plus(integer2).to_string();
            break;
        case '-':
            result = integer1.minus(integer2).to_string();
            break;
        case '*':
            result = integer1.multiply(integer2).to_string();
            break;
        default:
            throw std::runtime_error{"Invalid syntax or unimplemented syntax"};
    }
    return result;
}

int exec() {
    cout << INFO;
    string line;
    while (true) {
        // Read command line(operands and operator) from standard input.
        cout << ">>> ";
        getline(cin, line);
        if (cin.eof() || line == "exit") {
            return 0;
        } else if (line.empty()) {
            continue;
        }
        try {
            cout << eval(line) << endl;
        } catch (std::runtime_error &e) {
            cerr << "[Error] Traceback \n"
                    "  In <stdin>: " << line << endl
                 << "Syntax Error: " << e.what() << endl;
        } catch (...) {
            cerr << "[Warning] Traceback \n"
                    "  In <stdin>: " << line << endl
                 << "Input Ignored Warning: Syntax in line is not supported." << endl;
        }
    }
}

int exec_file(const string &file) {
    ifstream fin(file);
    ofstream fout(file + "_out.txt");
    if ((!fin.is_open()) || (!fout.is_open())) {
        cerr << "invalid file path." << endl;
        return -1;
    }
    string line;
    while (!fin.eof()) {
        // Read command line(operands and operator) from file.
        getline(fin, line);
        if (line.empty()) {
            continue;
        }
        try {
            fout << eval(line) << endl;
        } catch (std::runtime_error &e) {
            cerr << "[Error] Traceback \n"
                    "  In \"" + file + "\": " << line << endl
                 << "Syntax Error: " << e.what() << endl;
            return -2;
        } catch (...) {
            cerr << "[Error] Traceback \n"
                    "  In \"" + file + "\": " << line << endl
                 << "Input Ignored Warning: Syntax in line is not supported." << endl;
            return -3;
        }
    }
    fin.close();
    fout.close();
    return 0;
}

int main(int argc, char **argv) {
    if (argc >= 2) {
        return exec_file(argv[1]);
    }
    return exec();
}
