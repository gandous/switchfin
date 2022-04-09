cmake_minimum_required(VERSION 3.1)

project(gana)

set(CMAKE_CXX_STANDARD 17)


include_directories("${PROJECT_SOURCE_DIR}")

file(GLOB_RECURSE SRC "*")
add_library(gana ${SRC})
