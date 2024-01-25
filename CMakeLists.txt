project("CST")
cmake_minimum_required(VERSION 3.22)
add_executable("CST" main.cpp )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

add_definitions(-O3 -std=c++20)
add_subdirectory(client)
add_subdirectory(server)