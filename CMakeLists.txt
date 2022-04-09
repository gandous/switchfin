cmake_minimum_required(VERSION 3.1)


project(switchfin)

set(CMAKE_CXX_STANDARD 17)

if (SWITCH)
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

file(GLOB_RECURSE SRC "src/*")
add_executable(switchfin ${SRC})

target_compile_options(switchfin PRIVATE -g3 -Wall -Wextra)

target_link_libraries(switchfin gana)
if (SWITCH)
    set_target_properties(switchfin PROPERTIES
    APP_TITLE "switchfin"
    APP_AUTHOR " "
    APP_VERSION "0.1.0")

    target_link_libraries(switchfin -Wl,--whole-archive switch::libnx -Wl,--no-whole-archive)
    target_link_libraries(switchfin sfml-window-s sfml-graphics-s sfml-audio-s sfml-system-s FLAC vorbisfile vorbisenc vorbis ogg SDL2 EGL glapi GLESv2 glad drm_nouveau drm_nouveaud freetype bz2 png z gana)

    add_nro_target(switchfin)
else()
    target_link_libraries(switchfin sfml-window sfml-graphics sfml-audio sfml-system gana)
endif()

# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})