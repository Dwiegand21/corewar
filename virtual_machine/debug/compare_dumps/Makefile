
NAME			= dumpcmp

CC				= gcc
CFLAGS			= #-Wall -Wextra -Werror

SFILES			= main.c \
					read_processes_output.c \
					diff_output.c

HFILES			= compare_dumps.h

HEADERS			= $(addprefix $(INCDIR),$(HFILES))

OFILES			= $(addprefix $(OBJDIR),$(SFILES:.c=.o))

INC				= -I $(INCDIR)

SRCDIR			= ./sources/
OBJDIR			= ./objects/
INCDIR			= ./includes/

FT			= $(addprefix $(FT_DIR),$(FT_NAME))
FT_NAME		= libft.a
FT_DIR		= ../../libft
FT_INC		= -I $(FT_DIR)/includes
FT_LIB		= -L $(FT_DIR) -l ft

all: objects $(FT) $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) $(FT_LIB) -o $(NAME)

$(FT):
	make -C $(FT_DIR) build_static

objects:
	@mkdir -p objects

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(FT_INC) $(INC) -o $@ -c $<

clean:
	rm -f $(OFILES)
	make -C $(FT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT_DIR) fclean

re: fclean all