# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axtazy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 16:00:14 by dwiegand          #+#    #+#              #
#    Updated: 2019/08/25 07:49:05 by axtazy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

default_tagret: all

.PHONY: default_tagret

.NOTPARALLEL:
.SUFFIXES:

.SUFFIXES: .c .o .h .a


include makebuild/Config.make


all: $(DEFAULT_TARGETS)

.PHONY: all

build_all: build_dll build_so build_static

.PHONY: build_all

build_dll:
	@$(MAKE) -C ./makebuild -f Build.make

.PHONY: build_dll

build_so:
	@$(MAKE) -C ./makebuild -f Build.make

.PHONY: build_so

build_static:
	@$(MAKE) -C ./makebuild -f Build.make

.PHONY: build_static

clean:
	rm -f $(FT_OBJECT_FILES)
	rm -f $(FT_SHARED_OBJECTS_FILES)

.PHONY: clean

fclean: clean
	rm -f $(FT_TARGET_PATH)/libft.a
	rm -f $(FT_TARGET_PATH)/libft.dll
	rm -f $(FT_TARGET_PATH)/libft.so

.PHONY: fclean

re: fclean all

.PHONY: re


