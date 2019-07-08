cmake_minimum_required(VERSION 2.9)

project(corewar_exe C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

#add_link_options(-l )

FILE(GLOB LIBFT_SRCS
     /Users/ggerardy/CLION/corewar/virtual_machine/corewar/libft/*.c
     /Users/ggerardy/CLION/corewar/virtual_machine/corewar/libft/*/*.c)
include_directories(corewar/includes
                    libft/includes)

add_executable(corewar_exe corewar/sources/main.c
                                         corewar/sources/initialization.c
                                         corewar/sources/free_args.c
                                         corewar/sources/read_files.c
                                         corewar/sources/read_arguments.c
                                         corewar/sources/check_flags.c
                                         corewar/sources/globals.c
                                         corewar/sources/helpers.c
                                         corewar/sources/vm_operations1.c
                                         corewar/sources/vm_operations2.c
                                         corewar/sources/vm_operations3.c
                                         corewar/sources/vm_operations4.c
                                         corewar/sources/vm_map_ops.c
                                         corewar/sources/vm_ops_methods.c
                                         corewar/sources/vm_print_dump.c
                                         corewar/sources/vm_processes_ops.c
                                         corewar/sources/vm_game.c
                                         corewar/sources/ft_custom_tools.c
                                         corewar/sources/gleb_stuff/gvector.c
                                         corewar/includes/gvector.h)

#add_subdirectory(libft)

target_link_libraries(corewar_exe "${CMAKE_SOURCE_DIR}/libft/libft.a")
