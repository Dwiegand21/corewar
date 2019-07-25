
cmake_minimum_required(VERSION 3.14)



list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake_modules/sdl2)

#find_package(OpenGL REQUIRED)
#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_net REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_gfx REQUIRED)

find_package(SDL2)

if( SDL2_FOUND )
    set( SDL2_INC
            SDL2::Main
            SDL2::Image
            SDL2::Mixer
            SDL2::TTF
            OpenGL::GL
            )
    set( SDL2_LIB
            SDL2::Main
            SDL2::Image
            SDL2::Mixer
            SDL2::TTF
            OpenGL::GL
            )
else()
    set( LIBRARY_REPO

            )
    if ( NOT EXISTS "${CMAKE_SOURCE_DIR}/external/SDL-2.0.mirror5")
        message( STATUS " >>>> file was found")
    endif()
    add_subdirectory("${CMAKE_SOURCE_DIR}/external/SDL-2.0.mirror")
#    add_library(SDL2::Main2 UNKNOWN IMPORTED)
#    set_target_properties(SDL2::Main2 PROPERTIES
#            IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/SDL-2.0.mirror"
#            INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/SDL-2.0.mirror/include")
    set( SDL2_INC
            "${CMAKE_SOURCE_DIR}/external/SDL-2.0.mirror/include"
            )

    set( SDL2_LIB
            SDL2main
            )
endif()


