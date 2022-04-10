cmake_minimum_required(VERSION 3.9)
# Insert the name of your module here
project(ModuleName)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        ${PROJECT_NAME}
        test/Main.cpp
)