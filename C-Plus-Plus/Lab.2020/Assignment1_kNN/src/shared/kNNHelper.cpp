/********************************************************************************
 *  kNNRelease   Machine Learning Algorithms                                    *
 *  version  1.1        Based on the command line                               *
 *  Copyright (C) 2020  Holger Zhang   hzhang19@std.suda.edu.cn                 *
 *                                                                              *
 *  This file is part of kNN algorithms.                                        *
 *                                                                              *
 *  @file     kNNHelper.cpp                                                     *
 *  @include  <iostream>, <cmath>, <vector>, <string>, <fstream>                *
 *            <sstream>, <algorithm>, <stdexcept>, "kNNHelper.h"                *
 *  @brief    the implement of general auxiliary functions                      *
 *                                                                              *
 *  Namespace Helper    Auxiliary functions used in other files                 *
 *  Namespace Distance  Distance algorithms when calculating vector's distance  *
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
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "kNNHelper.h"

using namespace std;

/////////////////////////////////
// only reachable in this file //
/////////////////////////////////

namespace {
    struct NDVCompare {    // let the neighborDistance std::vector be comparable
        bool operator()(const std::vector<double> &left, const std::vector<double> &right) {
            return (left[0] < right[0]);
        }
    };
}

///////////////////////////////////
// Distance algorithms implement //
///////////////////////////////////

double Distance::euclid(const std::vector<double> &sample1, const std::vector<double> &sample2) {
    // Calculate the Euclidean distance of two data vectors
    double sum = 0.0;
    for (int i = 1; i < sample1.size(); ++i)
        sum += pow(sample1[i] - sample2[i], 2.0);
    return sqrt(sum);
}

double Distance::VectorAbs(const vector<double> &vec) {
    double sum = 0.0;
    for (int i = 1; i < vec.size(); ++i)
        sum += vec[i] * vec[i];
    return sqrt(sum);
}

double Distance::CosineSimilarity(const vector<double> &sample1, const vector<double> &sample2) {
    double tmp = 0.0;
    for (int i = 1; i < sample1.size(); ++i)
        tmp += sample1[i] * sample2[i];
    return tmp / (VectorAbs(sample1) * VectorAbs(sample2));
}

////////////////////////
//functions implement //
////////////////////////

double Helper::distance(const vector<double> &sample1, const vector<double> &sample2, int kind) {
    switch (kind) {
        case 0:
            return Distance::euclid(sample1, sample2);
        case 1:
            return Distance::CosineSimilarity(sample1, sample2);
        default:
            throw logic_error("Error distance type");
    }
}

int Helper::readTrainData(const string &filePath, vector<vector<double>> &dataSet, vector<string> &types) {
    ifstream fin(filePath, ios::in);
    if(!fin.is_open()){
        cout << "\n[ERROR] Can not open file " << filePath << endl;
        exit(1);
    }
    int dim;    // (dim:) the number of data in each line of file
    {   // get dim: the number of char ','
        string temp;
        getline(fin, temp);
        fin.seekg(0);   // back to file head
        dim = count(temp.begin(), temp.end(), ',');
    }
    while (!fin.eof()) {
        vector<double> data;    // typeID, data1, data2, ...
        {   // set typeID: the index of types
            string type;
            bool TypeFound = false;
            unsigned typeID; // the index of types
            getline(fin, type, ',');
            for (typeID = 0; typeID < types.size(); typeID++) {
                if (types[typeID] == type) {
                    TypeFound = true;
                    break;
                }
            }
            if (!TypeFound) {
                types.push_back(type);
                typeID = types.size() - 1;
            }
            data.push_back(typeID);
        }
        for (int i = 0; i < dim; i++) { // set each data
            string buff;
            getline(fin, buff, (i == dim - 1) ? '\n' : ',');
            data.push_back(atof(buff.c_str())); // from string to double
        }
        // set train set
        dataSet.push_back(data);
    }
    fin.close();
    return dim;
}

int Helper::getTypeID(int k, const vector<vector<double>> &train, const vector<double> &sample) {
    // build neighborDistances and sort it
    vector<vector<double>> neighborDistances;   // element: distance, typeID
    for (const auto &trainSample : train) {
        double dis = distance(sample, trainSample, _DISTANCE_TYPE);
        vector<double> neighbor({dis, trainSample[0]});
        neighborDistances.push_back(neighbor);
    }
    sort(neighborDistances.begin(), neighborDistances.end(), NDVCompare());

    // get k Nearest-Neighbors as possible typeIDs
    vector<vector<int>> possibleTypes;        // typeID, frequence
    for (int i = 0; i < k; i++) {            // get k Nearest-Neighbors
        int typeID = (int) neighborDistances[i][1];
        // count the frequency of appearance of each type
        bool typeIDFound = false;
        for (auto &possibleType : possibleTypes) {
            if (possibleType[0] == typeID) {
                possibleType[1]++;
                typeIDFound = true;
                break;
            }
        }
        if (!typeIDFound)
            possibleTypes.push_back(vector<int>{typeID, 1});
    }

    // find the most likely typeID: possibleTypes[result_pos][0]
    int result_pos = 0; // assume the frequency of pos 0 typeID is max
    for (int i = 0; i < possibleTypes.size(); i++)
        if (possibleTypes[i][1] > possibleTypes[result_pos][1])
            result_pos = i;

    return possibleTypes[result_pos][0];
}

int Helper::getEval(map<string, int> &res) {
    res.clear();
    ifstream inFile("eval.dat", ios::in);
    if (!inFile.is_open()) {
        setEval({ });
        return 1;
    }
    while (!inFile.eof()) {
        string file;
        int k;
        inFile >> file >> k;
        if (file.empty()) {
            break;
        }
        res.insert(make_pair(file, k));
    }
    inFile.close();
    return 0;
}

int Helper::setEval(const map<std::string, int> &res) {
    ofstream outFile("eval.dat", ios::out);
    for (const auto &elem : res) {
        outFile << elem.first << ' ' << elem.second << endl;
    }
    outFile.close();
    return 0;
}

