cmake_minimum_required(VERSION 3.14)
project(visualization C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        sources/main.c
        sources/initialization.c
        sources/myApplication.c )

include_directories(
        includes/
        external/soil-1.16/inc/
        external/glfw-3.4/include/
        external/glew-2.2.0/include/
        external/freeglut-3.0.0/freeglut/freeglut/include/ )

add_executable(visualization ${SOURCE_FILES})

add_subdirectory(external/glfw-3.4 EXCLUDE_FROM_ALL)

add_subdirectory(external/glew-2.2.0 EXCLUDE_FROM_ALL)

add_subdirectory(external/soil-1.16 EXCLUDE_FROM_ALL)

add_subdirectory(external/freeglut-3.0.0/freeglut/freeglut EXCLUDE_FROM_ALL)

target_link_libraries(visualization PRIVATE soil glfw libglew_static freeglut_static)
