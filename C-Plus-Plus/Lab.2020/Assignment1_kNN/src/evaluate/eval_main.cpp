/********************************************************************************
 *  kNNRelease   Machine Learning Algorithms                                    *
 *  version  1.1        Based on the command line                               *
 *  Copyright (C) 2020  Holger Zhang   hzhang19@std.suda.edu.cn                 *
 *                                                                              *
 *  This file is part of kNN algorithms.                                        *
 *                                                                              *
 *  @file     eval_main.cpp                                                     *
 *  @include  <iostream>, "eval_runner.h"                                       *
 *  @brief    the main function of module evaluate                              *
 *                                                                              *
 *  @author   Holger Zhang                                                      *
 *  @email    hzhang19@std.suda.edu.cn                                          *
 *  @version  1.1                                                               *
 *  @date     2020/04/10                                                        *
 *                                                                              *
 *------------------------------------------------------------------------------*
 *  Change History :                                                            *
 *  <Date>     | <Version> | <Author>       | <Description>                     *
 *------------------------------------------------------------------------------*
 *  2020/04/10 | 1.0       | Holger Zhang   | Create file                       *
 *  2020/05/02 | 1.1       | Holger Zhang   | Restructure                       *
 *------------------------------------------------------------------------------*
 *                                                                              *
 ********************************************************************************/

#include <iostream>
#include "eval_runner.h"

using namespace std;
using namespace Evaluate;

int main(int argc, char *argv[]) {
    string file;
    // check before running
    if (argc < 2) {
        cout << "Invalid argument is given." << endl;
        help();
        return 0;
    }

    file = string(argv[1]);
    cout << "[INFO] Getting k." << endl;
    pair<int, double> result;
    if (argc == 3) {
        result = runner(file, atoi(argv[2]));
    } else {
        result = runner(file);
    }
    cout << "Using k = " << result.first << ", the precision is " << result.second * 100 << '%' << endl;

    cout << "\n[INFO] See you later!" << endl;
    return 0;
}

