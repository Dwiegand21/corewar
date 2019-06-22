
cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/sdl2)
#
find_package(OpenGL REQUIRED)
#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)

add_subdirectory(glfw-3.4 EXCLUDE_FROM_ALL)

add_subdirectory(glew-2.2.0 EXCLUDE_FROM_ALL)

add_subdirectory(soil-1.16 EXCLUDE_FROM_ALL)

add_subdirectory(freeglut-3.0.0/freeglut/freeglut EXCLUDE_FROM_ALL)

add_subdirectory(SDL-2.0.mirror)

set(PROPERTIES LIBRARIES
        soil
        glfw
        libglew_static
        freeglut_static
        SDL2main
        SDL2image
        OpenGL::GL
        OpenGL::GLU )

set( INCLUDES
        soil-1.16/inc/
        glfw-3.4/include/
        glew-2.2.0/include/
        freeglut-3.0.0/freeglut/freeglut/include/
        SDL-2.0.mirror/include
        OpenGL::GL
        OpenGL::GLU )

