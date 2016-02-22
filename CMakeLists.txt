cmake_minimum_required(VERSION 3.3)
project(splay_next_permutation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp splay_node.cpp)
add_executable(splay_next_permutation ${SOURCE_FILES})