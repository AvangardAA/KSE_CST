cmake_minimum_required(VERSION 3.22)
project(CST_HW3)

file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

foreach(source IN LISTS Sources)
    get_filename_component(exec ${source} NAME_WE)
    add_executable(${exec} ${source})
endforeach()
