cmake_minimum_required(VERSION 3.14)
project(visualization C)

include(./external/AddLibraries.cmake)

set(CMAKE_C_STANDARD 99)

set( SOURCE_FILES
        sources/main.c
        sources/create_window.c
#        sources/SDL_example.c
        sources/initialization.c
        sources/destroy_all.c
        sources/game_page.c
        sources/title_page.c
        sources/globals.c
        sources/load_game_page.c
        sources/load_title_page.c
        sources/menu_bar.c
        sources/create_renderer.c sources/create_texture.c sources/create_cursor.c)

add_executable(visualization ${SOURCE_FILES})

target_include_directories( visualization PRIVATE
        ./includes/
#        SDL2::Main
#        SDL2::Image
#        SDL2::Mixer
#        SDL2::TTF
#        OpenGL::GL
        "${SDL2_INC}"
        )

target_link_libraries( visualization PRIVATE
#        SDL2::Main
#        SDL2::Image
#        SDL2::Mixer
#        SDL2::TTF
#        OpenGL::GL
        "${SDL2_LIB}"
        )
