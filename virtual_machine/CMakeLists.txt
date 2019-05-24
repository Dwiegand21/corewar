cmake_minimum_required(VERSION 3.14)

project(virtual_machine C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(EXE_FILES   sources/main.c )

target_include_directories(virtual_machine includes)

add_executable(virtual_machine ${EXE_FILES})
