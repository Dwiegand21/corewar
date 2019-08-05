cmake_minimum_required(VERSION 3.10)
project(visualization C)

include( ${CMAKE_SOURCE_DIR}/cmake/AddLibraries.cmake )

set( TARGET visualization)

set( CMAKE_C_STANDARD 99 )

set( SOURCE_FILES
        sources/main.c
        sources/create_window.c
        sources/initialization.c
        sources/destroy_all.c
        sources/game_page.c
        sources/title_page.c
        sources/globals.c
        sources/game_page_load.c
        sources/title_page_load.c
        sources/menu_bar.c
        sources/create_renderer.c
        sources/create_texture.c
        sources/create_cursor.c
        sources/title_page_events_states.c
        )

add_executable(${TARGET} ${SOURCE_FILES})

target_include_directories( ${TARGET} PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
        )

target_include_directories( ${TARGET} PRIVATE
        SDL2::Main
        SDL2::Image
        SDL2::Mixer
        SDL2::TTF
        )

target_link_libraries( visualization PRIVATE
        SDL2::Main
        SDL2::Image
        SDL2::Mixer
        SDL2::TTF
        )

set_property( TARGET ${TARGET}
        PROPERTY
        C_STANDART 99
        )
set_property( TARGET ${TARGET}
        PROPERTY
        C_STANDART_REQUIRED ON
        )
