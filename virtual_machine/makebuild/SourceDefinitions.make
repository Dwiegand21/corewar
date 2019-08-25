
__PROJECT_MAIN_DIR		:= $(shell cd ..; pwd)

__CONFIGS_DIR			:= $(__PROJECT_MAIN_DIR)/makebuild
__SOURCES_DIR			:= $(__PROJECT_MAIN_DIR)/sources
__INCLUDES_DIR			:= $(__PROJECT_MAIN_DIR)/includes
__OBJECTS_DIR			:= $(__PROJECT_MAIN_DIR)/objects
__DEPENDENCY_DIR		:= $(__PROJECT_MAIN_DIR)/dependencies
__LIBRARIES_DIR			:= $(__PROJECT_MAIN_DIR)/libft
__BUILD_DIRS			:= $(__OBJECTS_DIR)

__OBJECT_FILES			= $(addprefix $(__OBJECTS_DIR)/,$(__SOURCE_FILES:%.c=%.o))

__SOURCE_FILES			:=  \
					main.c \
					globals.c \
					helpers.c \
					initialization.c \
					read_arguments.c \
					check_flags.c \
					read_files.c \
					free_args.c \
					vm_operations1.c \
					vm_operations2.c \
					vm_operations3.c \
					vm_operations4.c \
					vm_ops_methods.c \
					vm_map_ops.c \
					vm_game.c \
					vm_print_dump.c \
					vm_processes_ops.c \
					ft_vm_vector_int.c \
					ft_vm_vector_prc.c \
					ft_vm_vector_rng.c \
					timsort.c \
					timsort_merge.c