cmake_minimum_required(VERSION 3.9)
project(InvertedIndex)

set(CMAKE_CXX_STANDARD 14)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)


add_executable(
        ${PROJECT_NAME}
        test/Main.cpp
)
