cmake_minimum_required(VERSION 3.24)
project(data_structures)

set(CMAKE_CXX_STANDARD 11)

add_executable(data_structures main.cpp ds/vector.h ds/list.h ds/avl-tree.h)
