cmake_minimum_required(VERSION 3.16)
project(InfixExpression)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(util/container Container)

add_executable(InfixExpressionCalculator
        ${Container}
        util/infix_expression.cpp
        util/infix_expression.h
        main.cpp)