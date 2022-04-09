cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)


include_directories(nanovg PRIVATE "src")

file(GLOB_RECURSE NANOVG_SRC "src/*")
add_library(nanovg ${NANOVG_SRC})
