project("CST_Client")
cmake_minimum_required(VERSION 3.22)
add_executable("client" client.cpp)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/client)

file(GLOB_RECURSE Sources 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

target_sources(client PRIVATE ${Sources})