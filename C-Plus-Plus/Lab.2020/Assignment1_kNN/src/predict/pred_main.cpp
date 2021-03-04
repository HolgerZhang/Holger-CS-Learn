/********************************************************************************
 *  kNNRelease   Machine Learning Algorithms                                    *
 *  version  1.1        Based on the command line                               *
 *  Copyright (C) 2020  Holger Zhang   hzhang19@std.suda.edu.cn                 *
 *                                                                              *
 *  This file is part of kNN algorithms.                                        *
 *                                                                              *
 *  @file     pred_main.cpp                                                     *
 *  @include  <iostream>, "pred_runner.h"                                       *
 *  @brief    the main function of module predict                                *
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
#include "pred_runner.h"
using namespace std;
using namespace Predict;

int main(int argc, char* argv[]) {
    string file;
    int k;

    if (argc < 2) {
        cout << "Invalid argument is given." << endl;
        help();
        return 0;
    }
    file = string(argv[1]);
    k = getK(file);
    runner(file, k);

    cout << "\n[INFO] See you later!" << endl;
    return 0;
}

