/********************************************************************************
 *  kNNRelease   Machine Learning Algorithms                                    *
 *  version  1.1        Based on the command line                               *
 *  Copyright (C) 2020  Holger Zhang   hzhang19@std.suda.edu.cn                 *
 *                                                                              *
 *  This file is part of kNN algorithms.                                        *
 *                                                                              *
 *  @file     pred_runner.h                                                     *
 *  @include  <string>, <vector>, "../shared/kNNHelper.h"                       *
 *  @brief    functions during predicting the sample                            *
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

#ifndef KNNRELEASE_RUNNER_H_P
#define KNNRELEASE_RUNNER_H_P

#include <string>
#include <vector>
#include "../shared/kNNHelper.h"


/**
 * @brief   functions during predicting the sample
 */
namespace Predict {

/**
 * <p> Get the type of test sample. </p>
 * @param k         kNN argument k
 * @param train     trainingSet
 * @param types     test sample
 * @param sample    test sample
 * @return          the most likely type of the test sample
 */
    inline std::string
    getType(int k, const std::vector<std::vector<double>>& train, const std::vector<std::string>& types, const std::vector<double>& sample);

/**
 * <p> <b>usage</b>: predict.exe file </p>
 * <p> use it when running. </p>
 * @param file      argv[1]
 * @param k         kNN argument k
 * @return          types
 */
    void runner(const std::string &file, int k);

/**
 * <p> Get the kNN argument k. </p>
 * @param file      argv[1]
 * @retur           kNN argument k
 */
    int getK(const std::string &file);

/**
 * <p> Show the usage of the module </p>
 */
    void help();
}

#endif //KNNRELEASE_RUNNER_H_P
