cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)


include_directories("include")

file(GLOB_RECURSE GLAD_SRC "src/*")
add_library(glad ${GLAD_SRC})
