cmake_minimum_required(VERSION 3.14)
project(visualization C)

set(CMAKE_C_STANDARD 99)

set( SOURCE_FILES
        sources/main.c
        sources/initialization.c
        sources/myApplication.c
        sources/GLUT_example.c
        sources/SDL_example.c
        sources/GLFW_example.c)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/cmake_modules/sdl2)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
        includes/
        external/soil-1.16/inc/
        external/glfw-3.4/include/
        external/glew-2.2.0/include/
        external/freeglut-3.0.0/freeglut/freeglut/include/
        SDL2::Main
        SDL2::Image
        OpenGL::GL
        OpenGL::GLU )

add_executable(visualization ${SOURCE_FILES})

add_subdirectory(external/glfw-3.4 EXCLUDE_FROM_ALL)

add_subdirectory(external/glew-2.2.0 EXCLUDE_FROM_ALL)

add_subdirectory(external/soil-1.16 EXCLUDE_FROM_ALL)

add_subdirectory(external/freeglut-3.0.0/freeglut/freeglut EXCLUDE_FROM_ALL)

target_link_libraries( visualization PRIVATE
        soil
        glfw
        libglew_static
        freeglut_static
        SDL2::Main
        SDL2::Image
        OpenGL::GL
        OpenGL::GLU )
