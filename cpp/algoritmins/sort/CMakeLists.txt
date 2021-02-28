cmake_minimum_required(VERSION 3.9)
project(SortAlgorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        ${PROJECT_NAME}
        Order.cpp
        test/Main.cpp)