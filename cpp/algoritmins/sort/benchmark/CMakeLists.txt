cmake_minimum_required(VERSION 3.9)
project(Benchmark)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


find_package(benchmark REQUIRED)

add_executable(
        ${PROJECT_NAME}
        Main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark)
