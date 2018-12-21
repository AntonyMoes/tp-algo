cmake_minimum_required(VERSION 3.13)
project(task1)

set(CMAKE_CXX_STANDARD 17)

set(
        Source

        CListGraph.cpp
        CListGraph.h
        IGraph.h CMatrixGraph.cpp CMatrixGraph.h CSetGraph.cpp CSetGraph.h CArcGraph.cpp CArcGraph.h)


add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR} )

add_executable(task1 main.cpp ${Source})
target_link_libraries(task1 gtest gtest_main gmock gmock_main pthread)
