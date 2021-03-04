/********************************************************************************
 *  kNNRelease   Machine Learning Algorithms                                    *
 *  version  1.1        Based on the command line                               *
 *  Copyright (C) 2020  Holger Zhang   hzhang19@std.suda.edu.cn                 *
 *                                                                              *
 *  This file is part of kNN algorithms.                                        *
 *                                                                              *
 *  @file     kNNHelper.h                                                       *
 *  @include  <map>                                                             *
 *  @brief    General auxiliary functions                                       *
 *                                                                              *
 *  Namespace Helper    Auxiliary functions used in other files                 *
 *  Namespace Distance  Distance algorithms when calculating vector's distance  *
 *  _DISTANCE_TYPE      Choose distance calculate method                        *
 *                0     Euclid distance (default)                               *
 *                1     Cosine Similarity                                       *
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

#ifndef KNNRELEASE_KNNHELPER_H
#define KNNRELEASE_KNNHELPER_H

#include <map>
#define _DISTANCE_TYPE  0


/**
 * @brief   Auxiliary functions used in other files
 */
namespace Helper {

/**
 * <p> Calculate the distance between sample1and sample2 </p>
 * <p> <b>SAMPLEVECTOR</b> : typeID, data1, data2, ... </p>
 * @param sample1   SAMPLEVECTOR
 * @param sample2   SAMPLEVECTOR
 * @param kind      the kind of algorithm(default: 0, from 0 to 1)
 * @return          Distance
 */
    double  distance(const std::vector<double> &sample1, const std::vector<double> &sample2, int kind = 0);

/**
 * <p> Initialize the data sample set with a text file </p>
 * @param filePath  the path to the file contains lines like "type,data1,data2,..."
 * @param dataSet   data set
 * @param types     typeSet
 * @ruturn          (dim:) the number of data in each line of file
 */
    int     readTrainData(const std::string &filePath, std::vector<std::vector<double>> &train, std::vector<std::string> &types);

/**
 * <p> Calculate the precision using testSet </p>
 * @param k         kNN argument k
 * @param train     trainingSet
 * @param sample    test sample
 * @return          the most likely typeID of the test sample
 */
    int     getTypeID(int k, const std::vector<std::vector<double>> &train, const std::vector<double> &sample);

/**
 * <p> Get Eval Map </p>
 * @param res       save Eval Map
 * @return          1 - failed to load data; 0: finished
 */
    int     getEval(std::map<std::string, int> &res);

/**
 * <p> Set Eval Map </p>
 * @param res       write Eval Map
 * @return          1 - failed to write data; 0: finished
 */
    int     setEval(const std::map<std::string, int> &res);
}


/**
 * @brief   Distance algorithms when calculating vector's distance
 */
namespace Distance {
    /**
     * @return      the Euclidean distance between sample1 and sample2
     */
    double euclid(const std::vector<double> &sample1, const std::vector<double> &sample2);

    /**
     * @param vec   SAMPLEVECTOR
     * @return      the abs of SAMPLEVECTOR (HELPer)
     */
    double VectorAbs(const std::vector<double> &vec);

    /**
     * @return      the Cosine Similarity between sample1 and sample2
     */
    double CosineSimilarity(const std::vector<double> &sample1, const std::vector<double> &sample2);

}


#endif //KNNRELEASE_KNNHELPER_H
