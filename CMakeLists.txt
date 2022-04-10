cmake_minimum_required(VERSION 3.1)


project(switchfin)

set(CMAKE_CXX_STANDARD 17)

if(SWITCH)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Switch)

    ## Required libraries and utilities

    # SwitchTools provide various helper functions for building Switch file formats.
    include(SwitchTools)

    find_package(Libnx REQUIRED)

    include_directories("${PORTLIBS}/include")
    include_directories("${LIBNX}/include")
    link_directories("${PORTLIBS}/lib")
endif()

add_subdirectory("lib")

include_directories("src")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/lib/")

file(GLOB_RECURSE SWITCHFIN_SRC "src/*")
add_executable(switchfin ${SWITCHFIN_SRC})

target_compile_options(switchfin PRIVATE -Wall -Wextra)

if (SWITCH)
    set_target_properties(switchfin PROPERTIES
    APP_TITLE "switchfin"
    APP_AUTHOR " "
    APP_VERSION "0.1.0")

    add_nro_target(switchfin)
endif()
target_link_libraries(switchfin gana)

# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})