cmake_minimum_required(VERSION 3.14)
project(visualization C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)

set(SOURCE_FILES sources/main.c)
add_executable(gtk_test ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(gtk_test ${GTK3_LIBRARIES})
