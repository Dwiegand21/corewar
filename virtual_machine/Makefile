
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
					bigendian_ops.c \
					helpers.c

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

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(FT_INC) $(INC) -o $@ -c $<

clean:
	rm -f $(OFILES)
	make -C $(FT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT_DIR) fclean

re: fclean all
