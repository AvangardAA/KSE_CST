project("CST_Server")
cmake_minimum_required(VERSION 3.22)
add_executable("server" server.cpp)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/server)

file(GLOB_RECURSE Sources 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

target_sources(server PRIVATE ${Sources})