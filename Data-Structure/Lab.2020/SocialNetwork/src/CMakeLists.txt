cmake_minimum_required(VERSION 3.16)
project(SocialNetwork)

set(CMAKE_CXX_STANDARD 11)

add_executable(social main.cpp social_graph.cpp social_graph.h)