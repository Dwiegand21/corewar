
__PROJECT_MAIN_DIR		:= $(shell pwd)

__CONFIGS_DIR			:= $(__PROJECT_MAIN_DIR)/makebuild
__SOURCES_DIR			:= $(__PROJECT_MAIN_DIR)/sources
__INCLUDES_DIR			:= $(__PROJECT_MAIN_DIR)/includes
__OBJECTS_DIR			:= $(__PROJECT_MAIN_DIR)/objects
__SHARED_OBJECTS_DIR	:= $(__PROJECT_MAIN_DIR)/shared_objects
__DEPENDENCY_DIR		:= $(__CONFIGS_DIR)/dependencies

__OBJECT_FILES			= $(addprefix $(__OBJECTS_DIR)/,$(__SOURCE_FILES:%.c=%.o))
__SHARED_OBJECT_FILES	= $(addprefix $(__SHARED_OBJECTS_DIR)/,$(__SOURCE_FILES:%.c=%.o))


__SOURCE_DIRECTORIES_PATHS := \
				$(__SOURCES_DIR)/ft_binary_heap \
                $(__SOURCES_DIR)/ft_iostream \
                $(__SOURCES_DIR)/ft_list \
                $(__SOURCES_DIR)/ft_matrix \
                $(__SOURCES_DIR)/ft_memory \
                $(__SOURCES_DIR)/ft_printf \
                $(__SOURCES_DIR)/ft_project_assets \
                $(__SOURCES_DIR)/ft_string \
                $(__SOURCES_DIR)/ft_vector

__SOURCE_FILES := \
				ft_atoi.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strclr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdel.c \
				ft_strdup.c \
				ft_strequ.c \
				ft_striter.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlen.c \
				ft_strmap.c \
				ft_strmapi.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strnequ.c \
				ft_strnequ_rev.c \
				ft_strnew.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strsplit.c \
				ft_strstr.c \
				ft_strsub.c \
				ft_strtrim.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_bzero.c \
				ft_memalloc.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memdel.c \
				ft_memmove.c \
				ft_memset.c \
				ft_realloc.c \
				ft_lstadd.c \
				ft_lstdel.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstadd_back.c \
				ft_lstcpy_elem.c \
				ft_lstforeach.c \
				ft_lstlen.c \
				ft_lstrev.c \
				ft_lstcpy.c \
				ft_lstrcpy.c \
				ft_lstsort.c \
				ft_lstswap.c \
				ft_putchar_fd.c \
				ft_putchar.c \
				ft_putendl_fd.c \
				ft_putendl.c \
				ft_putnbr_fd.c \
				ft_putnbr.c \
				ft_putstr_fd.c \
				ft_putstr.c \
				ft_get_next_line.c \
				ft_get_lines_to_lst.c \
				ft_vector_create.c \
				ft_vector_delete.c \
				ft_vector_delete_elem.c \
				ft_vector_begin.c \
				ft_vector_end.c \
				ft_vector_push_back.c \
				ft_vector_join.c \
				ft_vector_size.c \
				ft_vector_iter.c \
				ft_vector_iteri.c \
				ft_vector_tools.c \
				ft_bheap_extract.c \
				ft_bheap_get.c \
				ft_bheap_insert.c \
				ft_bheap_sift_down.c \
				ft_bheap_tools.c \
				ft_bheap_init.c \
				ft_error.c \
				ft_printf.c \
				ft_vprintf.c \
                init.c \
                init2.c \
                args.c \
                plist.c \
                tools.c \
                processing.c \
                preprocessing.c \
                postprocessing_1.c \
                postprocessing_2.c \
                checkers_1.c \
                checkers_2.c \
                ft_scale.c \
                char.c \
                char_tools.c \
                uni_encode.c \
                ldbl_1.c \
                ldbl_2.c \
                ldbl_3.c \
                ldbl_4.c \
                validation.c \
                print_result.c \
                free_printf.c
