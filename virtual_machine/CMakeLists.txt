cmake_minimum_required(VERSION 2.9)

project(virtual_machine C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(EXE_FILES corewar/sources/main.c
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
    corewar/sources/vm_print_dump.c corewar/sources/vm_processes_ops.c corewar/sources/vm_game.c corewar/sources/timsort.c corewar/sources/ft_vm_vector_int.c corewar/includes/vm_vector.h corewar/sources/ft_vm_vector_prc.c corewar/sources/timsort_merge.c corewar/includes/timsort.h corewar/sources/ft_vm_vector_rng.c)

include_directories(corewar/includes
        libft/includes)

add_executable(corewar_exe ${EXE_FILES})

#add_subdirectory(${CMAKE_SOURCE_DIR}/libft)

target_link_libraries(corewar_exe ${CMAKE_SOURCE_DIR}/libft/libft.a)
