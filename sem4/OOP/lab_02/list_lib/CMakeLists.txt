cmake_minimum_required(VERSION 3.19)
project(list_lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(list_lib main.cpp base_container.h list.h list.hpp node.h node.hpp iterator.hpp iterator.h exceptions.h)