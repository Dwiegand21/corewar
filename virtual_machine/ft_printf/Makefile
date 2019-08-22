# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbradama <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/26 17:31:04 by lbradama          #+#    #+#              #
#    Updated: 2019/02/26 17:31:05 by lbradama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a

FILES		=	ft_printf.c \
				init.c \
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
				lft_1.c \
				lft_2.c \
				ldbl_1.c \
				ldbl_2.c \
				ldbl_3.c \
				ldbl_4.c \
				validation.c

OFILES		=	$(FILES:%.c=%.o)
CFILES		=	$(addprefix $(SDIR),$(FILES))

CC		= gcc
FLAGS	= -Wall -Wextra -Werror

SDIR	= ./src/
TDIR	= ./tests/
IDIR	= ./includes

all: $(NAME)

obj:
	mkdir -p $(ODIR)

%.o:$(SDIR)%.c
	gcc $(FLAGS) -I $(IDIR) -o $@ -c $<

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all
