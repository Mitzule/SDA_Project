cmake_minimum_required(VERSION 3.23)
project(sda_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(untitled)

add_executable(sda_project
        untitled/bstree.h
        untitled/main.cpp
        untitled/rbtree.h)
