cmake_minimum_required(VERSION 3.10)

project(cppmini CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o3")

add_subdirectory(lib/source)

add_subdirectory(code/source)
