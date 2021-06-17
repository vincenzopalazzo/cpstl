cmake_minimum_required(VERSION 3.9)
project(ThreadSafe)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        ${PROJECT_NAME}
        test/Main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
