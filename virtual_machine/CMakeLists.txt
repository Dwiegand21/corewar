cmake_minimum_required(VERSION 3.14)

project(virtual_machine C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(./libft/includes)

FILE(GLOB LIBFT_SRCS ./libft/*.c ./libft/*/*.c)

set(EXE_FILES   sources/main.c
                sources/initialisation.c
                sources/operations.c
                mylib/ft_error.c
                mylib/ft_print_endian.c
                mylib/ft_strnequ_rev.c
                mylib/free_args.c
                mylib/ft_bytes_reverse.c
                sources/node_ops.c
                sources/print_map.c)

include_directories(virtual_machine includes)

add_executable(virtual_machine ${LIBFT_SRCS} ${EXE_FILES})


