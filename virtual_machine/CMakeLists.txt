cmake_minimum_required( VERSION 3.10 )

project( virtual_machine C )

set( EXE_FILES
		sources/main.c
		sources/initialization.c
		sources/free_args.c
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
		sources/vm_ops_methods.c
		sources/vm_print_dump.c
		sources/vm_processes_ops.c
		sources/vm_game.c
		sources/timsort.c
		sources/ft_vm_vector_int.c
		includes/vm_vector.h
		sources/ft_vm_vector_prc.c
		sources/timsort_merge.c
		includes/timsort.h
		sources/ft_vm_vector_rng.c
		)

set( TARGET corewar )

add_executable( ${TARGET} ${EXE_FILES} )

target_link_libraries( ${TARGET} PRIVATE
		${CMAKE_SOURCE_DIR}/libft/libft.a
		)

target_include_directories( ${TARGET} PRIVATE
		includes
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
		)