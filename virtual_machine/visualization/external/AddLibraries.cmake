
#find_package(OpenGL REQUIRED)
#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_net REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_gfx REQUIRED)

cmake_minimum_required(VERSION 3.14)

list( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake_modules/sdl2 )

list( APPEND RequiredLibsList
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        )

list( LENGTH RequiredLibsList NumberOfLibs )

foreach( LibName IN ITEMS ${RequiredLibsList} )
    find_package( "${LibName}" REQUIRED)
    if( NOT ${LibName}_FOUND )
        message( STATUS "# - ${LibName} not found" )
    else()
        message( STATUS "# + ${LibName} found" )
        list( APPEND FoundLibs "${LibName}" )
        list( REMOVE_ITEM RequiredLibsList "${LibName}" )
    endif()
endforeach()

list( LENGTH RequiredLibsList ListLength)

if( ListLength EQUAL 0 )
    message( STATUS "# All libraries found" )
else()
    message( STATUS "# Libraries not found:" )
    foreach(LibName IN ITEMS ${RequiredLibsList} )
        string( REPLACE "2" "" HgPackLibName ${LibName} )
        string( CONCAT HgPackLibURL "https://hg.libsdl.org/" "${HgPackLibName}" )
        list( APPEND NotFoundLibsURL_List ${HgPackLibURL} )
        message( STATUS "    * ${LibName} : ${HgPackLibURL}" )
    endforeach()
    message( STATUS "# Install required libraries..." )
    foreach( TargetLibURL IN ITEMS ${NotFoundLibsURL_List} )
        string( REGEX REPLACE ".+(\\/)" "" LibDirName ${TargetLibURL} )
        if ( EXISTS ${CMAKE_SOURCE_DIR}/external/${LibDirName} )
            # Try install library from {current}/external/{libdir}.
            # If it сannot installed, remove directory and install library pack
            message( STATUS "# ${LibDirName} not found <<<<" )
        else()
            execute_process(
                    COMMAND rm -rf ${LibDirName}
                    COMMAND hg clone "${TargetLibURL}" ${LibDirName}
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external
            )
        endif()
    endforeach()
endif()

set( SDL2_INC
        SDL2::Main
        SDL2::Image
        SDL2::Mixer
        SDL2::TTF
        )
set( SDL2_LIB
        SDL2::Main
        SDL2::Image
        SDL2::Mixer
        SDL2::TTF
        )
