cmake_minimum_required(VERSION 3.16)
project(Search)

set(CMAKE_CXX_STANDARD 11)

add_executable(SearchTester main.cpp search_list.cpp search_list.h timer.hpp)