cmake_minimum_required(VERSION 3.1)

include_directories(gana PRIVATE ".")
include_directories(gana PRIVATE "${PROJECT_SOURCE_DIR}/lib")
include_directories(gana PRIVATE "${PROJECT_SOURCE_DIR}/lib/glad/include")

file(GLOB_RECURSE GANA_SRC "*")

add_library(gana ${GANA_SRC})
if (SWITCH)
    target_link_libraries(gana nanovg)
else()
    target_link_libraries(gana nanovg glad)
endif()

