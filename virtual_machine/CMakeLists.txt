cmake_minimum_required(VERSION 3.14)

project(virtual_machine C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(./libft/includes)

FILE(GLOB LIBFT_SRCS ./libft/*.c ./libft/*/*.c)

set(EXE_FILES   sources/main.c
                sources/initialization.c
                sources/operations.c
                sources/free_args.c
                sources/node_ops.c
                sources/read_files.c
                sources/read_arguments.c
                sources/check_flags.c
                sources/globals.c
                sources/helpers.c)

include_directories(virtual_machine includes)

add_executable(virtual_machine ${LIBFT_SRCS} ${EXE_FILES})


