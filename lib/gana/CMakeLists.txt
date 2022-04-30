cmake_minimum_required(VERSION 3.1)

include_directories(gana PRIVATE ".")
include_directories(gana PRIVATE "${PROJECT_SOURCE_DIR}/lib")
include_directories(gana PRIVATE "${PROJECT_SOURCE_DIR}/lib/glad/include")

file(GLOB_RECURSE GANA_SRC "*")

add_library(gana STATIC ${GANA_SRC})

target_compile_options(gana PRIVATE -Wall -Wextra)
if (SWITCH)
    target_link_libraries(gana -Wl,--whole-archive switch::libnx -Wl,--no-whole-archive)
    target_link_libraries(gana sfml-window-s sfml-audio-s sfml-system-s mpv freetype FLAC vorbisfile vorbisenc vorbis bz2 png z nanovg avfilter avcodec avformat avutil bz2 z swscale swresample fribidi ogg SDL2 EGL glapi GLESv2 glad drm_nouveau drm_nouveaud freetype ass freetype curl)
    # target_link_libraries(gana sfml-window-s sfml-audio-s sfml-system-s FLAC vorbisfile vorbisenc vorbis ogg SDL2 EGL glapi GLESv2 glad drm_nouveau drm_nouveaud bz2 png z nanovg)
else()
    target_link_libraries(gana sfml-window EGL GL sfml-graphics sfml-audio sfml-system nanovg glad mpv curl)
endif()