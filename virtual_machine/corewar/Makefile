
NAME		= corewar

CC			= gcc -O3
CFLAGS		= #-Wall -Wextra -Werror

SFILES		= main.c \
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
					ft_custom_tools.c \
					ft_vm_vector_int.c \
					ft_vm_vector_int_utils.c \
					ft_vm_vector_prc.c \
					ft_vm_vector_prc_utils.c \
					timsort.c \
					timsort_merge.c

HFILES		= virtual_machine.h \
					vm_types.h \
					vm_constants.h \
					vm_vector.h \
					timsort.h

HEADERS		= $(addprefix $(INCDIR),$(HFILES))

OFILES		= $(addprefix $(OBJDIR),$(SFILES:.c=.o))

INC			= -I $(INCDIR)

INCDIR		= ./includes/
SRCDIR		= ./sources/
OBJDIR		= ./objects/

FT			= $(addprefix $(FT_DIR),$(FT_NAME))
FT_NAME		= libft.a
FT_DIR		= ../libft
FT_INC		= -I $(FT_DIR)/includes
FT_LIB		= -L $(FT_DIR) -l ft


all: objects $(FT) $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) $(FT_LIB) -o $(NAME)

$(FT):
	@make -C $(FT_DIR) all

objects:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(FT_INC) $(INC) -o $@ -c $<

clean:
	rm -f $(OFILES)
	make -C $(FT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT_DIR) fclean

re: fclean all

recode:
	rm -f $(OFILES)
	rm -f $(NAME)
	make -C . all
