NAME = gg

NAME_ASM = $(addsuffix .s,$(NAME))
NAME_BYTE = $(addsuffix .cor,$(NAME))

all: $(NAME_BYTE)

$(NAME_BYTE): $(NAME_ASM)
	@../compiler/asm $(NAME_ASM)

clean:

fclean: clean
	@rm -f $(NAME_BYTE)

re: fclean all
