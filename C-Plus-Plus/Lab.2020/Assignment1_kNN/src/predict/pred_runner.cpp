/********************************************************************************
 *  kNNRelease   Machine Learning Algorithms                                    *
 *  version  1.1        Based on the command line                               *
 *  Copyright (C) 2020  Holger Zhang   hzhang19@std.suda.edu.cn                 *
 *                                                                              *
 *  This file is part of kNN algorithms.                                        *
 *                                                                              *
 *  @file     pred_runner.cpp                                                   *
 *  @include  <iostream>, "pred_runner.h"                                       *
 *  @brief    the implement of functions during predicting the sample           *
 *                                                                              *
 *  Namespace Predict    functions during predicting the sample                 *
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
using namespace Helper;

void Predict::help() {
/*
usage: predict.exe file
[or on linux : usage: ./predict file]

     file    the path to text file which contains lines like 'type,data1,data2,...'

The module will find the param k which suits the train data.
file and k will be written in the file 'eval.dat'.

 */
#ifdef _WIN32
    const char help_msg[] = "usage: predict.exe file\n\n     file    the path to text file which contains lines like 'type,data1,data2,...'\n\nThe module will find the param k which suits the train data.\nfile and k will be written in the file 'eval.dat'.\n";
#endif  // _WIN32
#ifdef linux
    const char help_msg[] = "usage: ./predict file\n\n     file    the path to text file which contains lines like 'type,data1,data2,...'\n\nThe module will find the param k which suits the train data.\nfile and k will be written in the file 'eval.dat'.\n";
#endif  // linux

    cout << help_msg << endl;
}

void Predict::runner(const string &file, int k) {
    vector<vector<double>> trainingSet;
    vector<string> typeSet;
    int dim = readTrainData(file, trainingSet, typeSet);
    cout << "[INFO] Using k = " << k << ", the dimension(dim) of the training data is " << dim << endl;

    int cnt = 0;
    cout << "Please input the number of query: "; cin >> cnt;

    while (cnt-- > 0) {
        vector<double> query = { -1.0 };
        cout << "\nPlease input " << dim << " double number(s) splited by space: ";
        for (int i = 0; i < dim; i++) {
            double temp;
            cin >> temp;
            query.push_back(temp);
        }
        cout << "This sample most possibly to be " << getType(k, trainingSet, typeSet, query) << endl;
    }

}

int Predict::getK(const string &file) {
    map<string, int> res;
    int cnt = 0;
    BACK_EXCEPTION:
    while (getEval(res) == 1);
    int k;
    try {
        k = res.at(file);
    } catch (out_of_range &e) {
        cout << "Rebuilt the k map..." << endl;
#ifdef _WIN32
        string cmd = "evaluate.exe ";
#endif // _WIN32
#ifdef linux
        string cmd = "./evaluate ";
#endif // linux
        cmd += file;
        if (system(cmd.c_str()) != 0) {
            cout << "\n[ERROR] An error occurred during getting k" << endl;
            exit(1);
        }
        cnt++;
        if (cnt >= 3) {
            cout << "\n[ERROR] An error occurred during getting k" << endl;
            exit(1);
        }
        goto BACK_EXCEPTION;
    }
    return k;
}

string Predict::getType(int k, const vector<vector<double>> &train, const vector<string> &types, const vector<double> &sample) {
    return types[getTypeID(k, train, sample)];
}
