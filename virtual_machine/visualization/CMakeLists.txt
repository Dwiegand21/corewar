cmake_minimum_required(VERSION 3.10)
project(visualization C)

include( ${CMAKE_SOURCE_DIR}/cmake/AddLibraries.cmake )
#include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/AddLibraries_helper.cmake )

set( CMAKE_C_STANDARD 99 )

set( SOURCE_FILES
        sources/main.c
        sources/create_window.c
        sources/initialization.c
        sources/destroy_all.c
        sources/game_page.c
        sources/title_page.c
        sources/globals.c
        sources/load_game_page.c
        sources/title_page_load.c
        sources/menu_bar.c
        sources/create_renderer.c
        sources/create_texture.c
        sources/create_cursor.c
        )

add_executable(visualization ${SOURCE_FILES})

target_include_directories( visualization PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
        )

target_include_directories( visualization PRIVATE
#        SDL2::Main
#        SDL2::Image
#        SDL2::Mixer
#        SDL2::TTF
#        OpenGL::GL
        ${SDL2_INC}
        )

target_link_libraries( visualization PRIVATE
#        SDL2::Main
#        SDL2::Image
#        SDL2::Mixer
#        SDL2::TTF
#        OpenGL::GL
        ${SDL2_LIB}
        )
