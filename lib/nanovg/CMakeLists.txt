cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)

# Required otherwise we get multiplce definition of stb lib function
add_compile_definitions(NVG_NO_STB=1)

include_directories(nanovg PRIVATE "src")

file(GLOB_RECURSE NANOVG_SRC "src/*")
add_library(nanovg STATIC ${NANOVG_SRC})
