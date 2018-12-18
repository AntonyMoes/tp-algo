cmake_minimum_required(VERSION 3.13)
project(task1)

set(CMAKE_CXX_STANDARD 17)

set(
        Source

        CListGraph.cpp
        CListGraph.h
        IGraph.h)

add_executable(task1 main.cpp ${Source})