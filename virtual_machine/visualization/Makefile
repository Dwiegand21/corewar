
NAME		= visualization

CC			= gcc
CFLAGS		= -Wall -Wextra

GTK+INC		= `pkg-config --cflags gtk+-3.0`
GTK+LNK		= `pkg-config --libs gtk+-3.0`

SFILES		= main.c

IFILES		= visualization.h

OFILES		= $(addprefix $(OBJDIR),$(SFILES:.c=.o))

HEADERS		= $(addprefix $(INCDIR),$(IFILES))
INC			= -I $(INCDIR)

SRCDIR		= ./sources/
OBJDIR		= ./objects/
INCDIR		= ./includes/

all: $(NAME)

$(NAME): objects $(OFILES)
	gcc $(OFILES) $(GTK+LNK) -o $(NAME)

objects:
	@mkdir $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(GTK+INC) $(INC) -o $@ -c $<


clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
