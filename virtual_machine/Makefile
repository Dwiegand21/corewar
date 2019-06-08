
NAME		= corewar

CC			= gcc
CFLAGS		= #-Wall -Wextra -Werror

SFILES		= main.c \
					globals.c \
					initialization.c \
					read_arguments.c \
					check_flags.c \
					read_files.c \
					processes_ops.c \
					free_args.c \
					vm_operations1.c \
					vm_operations2.c \
					vm_operations3.c \
					vm_operations4.c \
					vm_ops_methods.c \
					vm_map_ops.c \
					vm_game.c \
					dump.c \
					helpers.c

HFILES		= virtual_machine.h \
					vm_types.h \
					vm_constants.h

HEADERS		= $(addprefix $(INCDIR),$(HFILES))

OFILES		= $(addprefix $(OBJDIR),$(SFILES:.c=.o))

INC			= -I $(INCDIR)

INCDIR		= ./includes/
SRCDIR		= ./sources/
OBJDIR		= ./objs/

FT			= $(addprefix $(FT_DIR),$(FT_NAME))
FT_NAME		= libft.a
FT_DIR		= ./libft
FT_INC		= -I $(FT_DIR)
FT_LIB		= -L $(FT_DIR) -l ft


all: objs $(FT) $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) $(FT_LIB) -o $(NAME)

$(FT):
	@make -C $(FT_DIR) all

objs:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(FT_INC) $(INC) -o $@ -c $<

dump:
	make -C compare_dumps re
	rm -f dumpcmp
	ln -s ./compare_dumps/dumpcmp ./dumpcmp

dumpcmp-fclean:
	rm -f dumpcmp
	make -C compare_dumps fclean

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
