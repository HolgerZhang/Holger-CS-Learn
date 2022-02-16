cmake_minimum_required(VERSION 3.6)
project(lexer-holger)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(lexer tools_kernel)
aux_source_directory(tools tools_kernel)

add_executable(myt ${lexer_kernel} ${tools_kernel} lexer.h tools.h myt.cpp)
add_executable(subset-construction ${lexer_kernel} ${tools_kernel} lexer.h tools.h subset.cpp)
add_executable(minimize ${lexer_kernel} ${tools_kernel} lexer.h tools.h minimize.cpp)