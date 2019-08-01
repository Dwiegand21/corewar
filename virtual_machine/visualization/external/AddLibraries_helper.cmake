
cmake_minimum_required(VERSION 3.10)

set( SDL2_INC )
set( SDL2_LIB )

#set( SDL2_PATH "${CMAKE_SOURCE_DIR}/external/SDL" )

#list( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake_modules/sdl2 )

list( APPEND RequiredLibsList
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        )

#foreach( LibName IN ITEMS ${RequiredLibsList} )
#    find_package(${LibName} REQUIRED )
#endforeach()

#add_subdirectory( ${CMAKE_SOURCE_DIR}/external/SDL EXCLUDE_FROM_ALL )
#add_subdirectory( ${CMAKE_SOURCE_DIR}/external/SDL_ttf EXCLUDE_FROM_ALL )

find_package( SDL2 )

list( APPEND SDL2_INC
        ${CMAKE_SOURCE_DIR}/external/SDL/include
        ${CMAKE_SOURCE_DIR}/external/SDL_ttf
        )

list( APPEND ${SDL2_LIB}
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        )