cmake_minimum_required(VERSION 3.16)
project(BigIntegerCalculator)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(util/container Container)

add_executable(IntegerCalculator
        ${Container}
        util/integer.h
        util/integer.cpp
        calculator.cpp)
