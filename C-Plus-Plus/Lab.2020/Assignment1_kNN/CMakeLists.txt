cmake_minimum_required(VERSION 3.5)

project(kNN)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BULID_TYPE "Release")

AUX_SOURCE_DIRECTORY(./src/shared/ SRC_SHARE)
AUX_SOURCE_DIRECTORY(./src/predict/ SRC_PRED)
AUX_SOURCE_DIRECTORY(./src/evaluate/ SRC_EVAL)

add_executable(evaluate ${SRC_SHARE} ${SRC_EVAL})
add_executable(predict ${SRC_SHARE} ${SRC_PRED})


