
NAME			= dumpcmp

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

SFILES			= main.c \
					read_processes_output.c \
					diff_output.c \
					helpers.c

HFILES			= compare_dumps.h

HEADERS			= $(addprefix $(IDIR),$(HFILES))

OFILES			= $(addprefix $(ODIR),$(SFILES:.c=.o))

SDIR			= ./sources/
ODIR			= ./objects/
IDIR			= ./includes/

INC				= -I $(IDIR)

all: objects $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME)

objects:
	@mkdir -p objects

$(ODIR)%.o: $(SDIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all