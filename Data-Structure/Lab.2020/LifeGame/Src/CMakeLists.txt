cmake_minimum_required(VERSION 3.16)
project(LifeGame)

set(CMAKE_CXX_STANDARD 11)

add_executable(LifeGame main.cpp life.cpp life.h console_runtime.cpp console_runtime.h)