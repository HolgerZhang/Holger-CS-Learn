cmake_minimum_required(VERSION 3.7)
project(exp04 C)

set(CMAKE_C_STANDARD 99)

add_executable(dynamic-memory dynamic-memory.c)
add_executable(page-replacement page-replacement.c)
add_executable(mm1 mm1-f.c)
add_executable(mm2 mm_full.c)