cmake_minimum_required(VERSION 3.9)
project(fenwicktree)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        ${PROJECT_NAME}
        Main.cpp
        FenwickTree.cpp)