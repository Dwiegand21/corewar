
#find_package(OpenGL REQUIRED)
#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_net REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_gfx REQUIRED)

cmake_minimum_required(VERSION 3.10)

list( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake_modules/sdl2 )

list( APPEND RequiredLibsList
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        )


foreach( LibName IN ITEMS ${RequiredLibsList} )
    find_package( "${LibName}" REQUIRED )
endforeach()
