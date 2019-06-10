# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axtazy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 16:00:14 by dwiegand          #+#    #+#              #
#    Updated: 2019/06/10 14:51:17 by axtazy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

.SUFFIX: .c .o .h .a

# Files from 'ft_string'
SFILES1			= ft_atoi.c \
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
					ft_toupper.c

# Files from 'ft_memory'
SFILES2			= ft_bzero.c \
					ft_memalloc.c \
					ft_memccpy.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memdel.c \
					ft_memmove.c \
					ft_memset.c

# Files from 'ft_list'
SFILES3			= ft_lstadd.c \
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
					ft_lstswap.c

# Files from 'ft_oistream'
SFILES4			= ft_putchar_fd.c \
					ft_putchar.c \
					ft_putendl_fd.c \
					ft_putendl.c \
					ft_putnbr_fd.c \
					ft_putnbr.c \
					ft_putstr_fd.c \
					ft_putstr.c \
					ft_get_next_line.c \
					ft_get_lines_to_lst.c

# Files from 'ft_queue'
SFILES5			= queue.c \
					queue2.c

# Files from 'ft_stack'
SFILES6			= stack.c \
					stack2.c

# Files from 'ft_matrix'
SFILES7			= matrix.c

# Files from 'ft_project_assets'
SFILES8			= ft_global.c \
					ft_project_name_init.c \
					ft_error.c

IFILES			= libft.h

OFILES			= $(addprefix $(OBJDIR),$(SFILES1:.c=.o)) \
					$(addprefix $(OBJDIR),$(SFILES2:.c=.o)) \
					$(addprefix $(OBJDIR),$(SFILES3:.c=.o)) \
					$(addprefix $(OBJDIR),$(SFILES4:.c=.o)) \
					$(addprefix $(OBJDIR),$(SFILES5:.c=.o)) \
					$(addprefix $(OBJDIR),$(SFILES6:.c=.o)) \
					$(addprefix $(OBJDIR),$(SFILES7:.c=.o)) \
					$(addprefix $(OBJDIR),$(SFILES8:.c=.o))

HEADERS			= $(addprefix $(INCDIR),$(IFILES))


SRCDIR1			= ./sources/ft_string/
SRCDIR2			= ./sources/ft_memory/
SRCDIR3			= ./sources/ft_list/
SRCDIR4			= ./sources/ft_iostream/
SRCDIR5			= ./sources/ft_queue/
SRCDIR6			= ./sources/ft_stack/
SRCDIR7			= ./sources/ft_matrix/
SRCDIR8			= ./sources/ft_project_assets/

INCDIR			= ./includes/
OBJDIR			= ./objects/

INC				= -I $(INCDIR)

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

$(OBJDIR)%.o: $(SRCDIR1)%.c $(INCDIR)ft_string.h
	gcc $(CFLAGS) $(INC) -o $@ -c $<

$(OBJDIR)%.o: $(SRCDIR2)%.c $(INCDIR)ft_memory.h
	gcc $(CFLAGS) $(INC) -o $@ -c $<

$(OBJDIR)%.o: $(SRCDIR3)%.c $(INCDIR)ft_list.h
	gcc $(CFLAGS) $(INC) -o $@ -c $<

$(OBJDIR)%.o: $(SRCDIR4)%.c $(INCDIR)ft_iostream.h
	gcc $(CFLAGS) $(INC) -o $@ -c $<

$(OBJDIR)%.o: $(SRCDIR5)%.c $(INCDIR)ft_queue.h
	gcc $(CFLAGS) $(INC) -o $@ -c $<

$(OBJDIR)%.o: $(SRCDIR6)%.c $(INCDIR)ft_stack.h
	gcc $(CFLAGS) $(INC) -o $@ -c $<

$(OBJDIR)%.o: $(SRCDIR7)%.c $(INCDIR)ft_matrix.h
	gcc $(CFLAGS) $(INC) -o $@ -c $<

$(OBJDIR)%.o: $(SRCDIR8)%.c $(INCDIR)ft_project_assets.h
	gcc $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
