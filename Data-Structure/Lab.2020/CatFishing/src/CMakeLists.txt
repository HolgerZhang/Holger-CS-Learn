cmake_minimum_required(VERSION 3.16)
project(CatFishing)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(util/container Container)

add_executable(CatFishing
        ${Container}
        solution.hpp
        main.cpp util/container/node.h)
