cmake_minimum_required(VERSION 3.14)
project(visualization C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES sources/main.c sources/initialization.c sources/myApplication.c)

add_executable(visualization ${SOURCE_FILES})

add_subdirectory(external/glfw-3.4 EXCLUDE_FROM_ALL)

add_subdirectory(external/glew-2.2.0 EXCLUDE_FROM_ALL)

include_directories(includes)

target_link_libraries(visualization glfw libglew_static)
