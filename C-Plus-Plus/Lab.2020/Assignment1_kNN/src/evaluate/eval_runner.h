/********************************************************************************
 *  kNNRelease   Machine Learning Algorithms                                    *
 *  version  1.1        Based on the command line                               *
 *  Copyright (C) 2020  Holger Zhang   hzhang19@std.suda.edu.cn                 *
 *                                                                              *
 *  This file is part of kNN algorithms.                                        *
 *                                                                              *
 *  @file     eval_runner.h                                                     *
 *  @include  <string>, <vector>, "../shared/kNNHelper.h"                       *
 *  @brief    functions during evaluating the sample                            *
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

#ifndef KNNRELEASE_RUNNER_H_E
#define KNNRELEASE_RUNNER_H_E

#include <string>
#include <vector>
#include "../shared/kNNHelper.h"


/**
 * @brief   functions during evaluating the sample
 */
namespace Evaluate {

/**
 * <p> initialize the training and test sample sets with a text file </p>
 * @param filePath  the path to the file contains lines like "type,data1,data2,..."
 * @param train     trainingSet
 * @param test      testSet
 * @param types     typeSet
 * @param testRange the range of test set
 */
    void setTrainingandTestSet(const std::string &, std::vector<std::vector<double>> &, std::vector<std::vector<double>> &,
                                 std::vector<std::string> &, int testRange = 30);

/**
 * <p> Calculate the precision using testSet </p>
 * @param k         kNN argument k
 * @param train     trainingSet
 * @param test      testSet
 * @return          precision of the result of testSet
 */
    double getPrecision(int k, const std::vector<std::vector<double>> &, const std::vector<std::vector<double>> &);

/**
 * <p> Show the usage of the module </p>
 */
    void help();

/**
 * <p> <b>usage</b>: evaluate.exe file [range] </p>
 * <p> use it when running. </p>
 * @param file      argv[1]
 * @param range     int(argv[2])
 * @return          precision, k
 */
    std::pair<int, double> runner(const std::string &file, int range = 30);
}

#endif //KNNRELEASE_RUNNER_H_E
