cmake_minimum_required(VERSION 3.16)
project(CH2)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(list List)

add_executable(Lab2 ${List} set.hpp Lab2.cpp)
add_executable(Lab3 ${List} warehouse.h warehouse.cpp Lab3.cpp)
