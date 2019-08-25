cmake_minimum_required( VERSION 3.10 )

project( virtual_machine C )

set( EXE_FILES
        corewar/sources/main.c
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
        corewar/sources/timsort.c
        corewar/sources/ft_vm_vector_int.c
        corewar/includes/vm_vector.h
        corewar/sources/ft_vm_vector_prc.c
        corewar/sources/timsort_merge.c
        corewar/includes/timsort.h
        corewar/sources/ft_vm_vector_rng.c
        )

set( TARGET corewar )

add_executable( ${TARGET} ${EXE_FILES} )

target_link_libraries( ${TARGET} PRIVATE
        ${CMAKE_SOURCE_DIR}/libft/libft.a
        )

target_include_directories( ${TARGET} PRIVATE
        corewar/includes
        libft/includes
        )

set_target_properties( ${TARGET} PROPERTIES
        C_STANDART 11
        C_STANDART_REQUIRED ON
        )

target_compile_options( ${TARGET} PRIVATE
        -Wall
        -Wextra
        -Werror
        )

target_compile_options( ${TARGET} PRIVATE
        -O2
        -march=native
        -Wshadow
        -Wundef
        -Wno-unused-result
        -D_FORTIFY_SOURCE=2
        -D TEST
        )