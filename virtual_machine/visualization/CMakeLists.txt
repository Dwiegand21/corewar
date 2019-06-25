cmake_minimum_required(VERSION 3.14)
project(visualization C)

include(./external/AddLibraries.cmake)

set(CMAKE_C_STANDARD 99)

set( SOURCE_FILES
        sources/main.c
        sources/SDL_example.c
        )

add_executable(visualization ${SOURCE_FILES})

target_include_directories( visualization PRIVATE
        includes/
        SDL2::Main
        SDL2::Image
        SDL2::Mixer
        SDL2::TTF
        OpenGL::GL
        )

target_link_libraries( visualization PRIVATE
        SDL2::Main
        SDL2::Image
        SDL2::Mixer
        SDL2::TTF
        OpenGL::GL
        )
