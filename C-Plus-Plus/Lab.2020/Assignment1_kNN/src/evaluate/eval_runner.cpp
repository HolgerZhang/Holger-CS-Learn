/********************************************************************************
 *  kNNRelease   Machine Learning Algorithms                                    *
 *  version  1.1        Based on the command line                               *
 *  Copyright (C) 2020  Holger Zhang   hzhang19@std.suda.edu.cn                 *
 *                                                                              *
 *  This file is part of kNN algorithms.                                        *
 *                                                                              *
 *  @file     eval_runner.cpp                                                   *
 *  @include  <iostream>, <cstdlib>, <ctime>, <map>, "eval_runner.h"            *
 *            <windows.h>(_WIN32), <zconf.h>(linux)								*
 *  @brief    the implement of functions during evaluating the sample           *
 *                                                                              *
 *  Namespace Evaluate    functions during evaluating the sample                *
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
#include <cstdlib>
#include <ctime>
#include <map>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#ifdef linux
#include <zconf.h>
#endif  // linux
#include "eval_runner.h"

using namespace std;
using namespace Helper;

void Evaluate::setTrainingandTestSet(const string &filePath, vector<vector<double>> &train, vector<vector<double>> &test,
                           vector<string> &types, int testRange) {
    vector<vector<double>> dataSet;
    readTrainData(filePath, dataSet, types);
    if (testRange > dataSet.size() / 2) {
        cerr << "WARNING: testRange is too large" << endl;
    }
    // set train set and test set
    unsigned chooseStep = dataSet.size() / testRange;
    srand(time(nullptr));
    int cnt = rand() % 5 + 1;    // random start
    for (int index = 0; index < dataSet.size(); index++, cnt++) {
        if (cnt % chooseStep != 0)
            train.push_back(dataSet[index]);
        else
            test.push_back(dataSet[index]);
    }
}

double Evaluate::getPrecision(int k, const vector<vector<double>> &train, const vector<vector<double>> &test) {
    int success = 0;    // the number of successful sample
    // traverse the test set(each sample: test[testIndex] -- typeID,data1,data2,...)
    for (const auto &testIndex : test) {
        int typeID = getTypeID(k, train, testIndex);
        // compare the most likely typeID with real typeID (test[testIndex][0])
        if (typeID == testIndex[0])
            success++;
    }
    return (double) success / test.size();
}

void Evaluate::help() {
/*
usage: evaluate.exe file [range]
[or on linux usage: ./evaluate file [range]]

     file    the path to text file which contains lines like 'type,data1,data2,...'
    range    (optional) default 30, the range of test sample set.
                        should not be more than half of the range of data sample set.

The module will find the param k which suits the train data.
file and k will be found in the file 'eval.dat'.

*/
#ifdef _WIN32
    const char help_msg[] = "usage: evaluate.exe file [range]\n\n     file    the path to text file which contains lines like 'type,data1,data2,...'\n    range    (optional) default 30, the range of test sample set.\n                        should not be more than half of the range of data sample set.\n\nThe module will find the param k which suits the train data.\nfile and k will be found in the file 'eval.dat'.\n\n";
#endif  // _WIN32
#ifdef linux
    const char help_msg[] = "usage: ./evaluate file [range]\n\n     file    the path to text file which contains lines like 'type,data1,data2,...'\n    range    (optional) default 30, the range of test sample set.\n                        should not be more than half of the range of data sample set.\n\nThe module will find the param k which suits the train data.\nfile and k will be found in the file 'eval.dat'.\n\n";
#endif // linux

    cout << help_msg << endl;
}

pair<int, double> Evaluate::runner(const string &file, int range) {
    map<int, double> paramK;    // k, precision
    pair<int, double> result(-1, 0);
    for (int k = 1; k < 20; k += 2) {
        vector<vector<double>> trainingSet;
        vector<vector<double>> testSet;
        vector<string> typeSet;

        Evaluate::setTrainingandTestSet(file, trainingSet, testSet, typeSet, range);
        paramK.insert(make_pair(k, getPrecision(k, trainingSet, testSet)));
        if (abs(paramK.at(k) - 1.0) < 1e-5) {
            result = make_pair(k, paramK.at(k));
            break;
        }
#ifdef _WIN32
        Sleep(1000);
#endif  // _WIN32
#ifdef linux
        sleep(1);
#endif  // linux
    }

    if (result.first == -1) {
        for (const auto &elem : paramK) {
            if (result.second < elem.second) {
                result.first = elem.first;
                result.second = elem.second;
            }
        }
    }

    map<std::string, int> evalMap;
    if (getEval(evalMap) == 1) {
        return result;
    }
    try {
        evalMap.at(file) = result.first;
    } catch (out_of_range &e) {
        evalMap.insert(make_pair(file, result.first));
    }
    if (setEval(evalMap) == 1) {
        return result;
    }
    return result;
}

