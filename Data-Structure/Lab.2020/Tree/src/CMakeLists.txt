cmake_minimum_required(VERSION 3.5)
project(TreeDemo)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(tree tree_src)
aux_source_directory(menu menu_src)

add_executable(BinaryTreeDemo main.cpp ${tree_src} ${menu_src} console.h console.cpp)