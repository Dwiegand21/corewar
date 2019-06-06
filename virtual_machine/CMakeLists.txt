cmake_minimum_required(VERSION 3.14)

project(virtual_machine C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(EXE_FILES   sources/main.c
                sources/initialization.c
                sources/free_args.c
                sources/processes_ops.c
                sources/read_files.c
                sources/read_arguments.c
                sources/check_flags.c
                sources/globals.c
                sources/helpers.c
                sources/vm_operations1.c
                sources/vm_operations2.c
                sources/vm_operations3.c
                sources/vm_operations4.c
        sources/vm_map_ops.c
                sources/vm_ops_methods.c sources/vm_game.c sources/dump.c)

include_directories(corewar includes
                            libft )

add_executable(corewar ${EXE_FILES})

add_subdirectory(libft)

target_link_libraries(corewar libft)
