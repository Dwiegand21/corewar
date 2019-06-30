# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 16:00:14 by dwiegand          #+#    #+#              #
#    Updated: 2019/06/30 14:58:45 by dwiegand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

.SUFFIX: .c .o .h .a

SFILES			=	ft_atoi.c \
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
					ft_bheap_create.c \
					ft_bheap_delete.c \
					ft_bheap_delete_elem.c \
					ft_bheap_extract.c \
					ft_bheap_get.c \
					ft_bheap_insert.c \
					ft_bheap_size.c \
					ft_bheap_get_vector.c \
					ft_bheap_tools.c \
					queue.c \
					queue2.c \
					stack.c \
					stack2.c \
					ft_global.c \
					ft_project_name_init.c \
					ft_error.c

IFILES			=	libft.h

OFILES			=	$(addprefix $(OBJDIR),$(SFILES:.c=.o))

HEADERS			=	$(addprefix $(INCDIR),$(IFILES))

INCDIR			=	./includes/
OBJDIR			=	./objects/

INC				=	-I $(INCDIR)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

$(OBJDIR)%.o: ./sources/ft_*/%.c $(INCDIR)/*
	gcc $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
