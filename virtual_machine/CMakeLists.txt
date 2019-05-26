cmake_minimum_required(VERSION 3.14)

project(virtual_machine C)

#set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(EXE_FILES   sources/main.c
                sources/initialisation.c
                sources/operations.c
                libft/ft_error.c
                libft/ft_print_endian.c
                libft/ft_strnequ_rev.c libft/free_args.c libft/bytes_reverse.c sources/node_ops.c sources/print_map.c libft/ft_memalloc.c)

include_directories(virtual_machine includes)

add_executable(virtual_machine ${EXE_FILES})
