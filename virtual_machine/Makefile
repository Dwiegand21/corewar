
EXE_PATH			= ./executable/

COREWAR_DIR			= ./corewar/
COREWAR_EXE_NAME	= corewar
COREWAR_EXE			= $(addprefix $(COREWAR_DIR),$(COREWAR_EXE_NAME))
COREWAR_COPY		= $(addprefix $(EXE_PATH),$(COREWAR_EXE_NAME))

CMPDUMP_DIR			= ./compare_dumps/
CMPDUMP_EXE_NAME	= dumpcmp
CMPDUMP_EXE			= $(addprefix $(CMPDUMP_DIR),$(CMPDUMP_EXE_NAME))
CMPDUMP_COPY		= $(addprefix $(EXE_PATH),$(CMPDUMP_EXE_NAME))

VISUAL_DIR			= ./visualization/
VISUAL_EXE_NAME		= visualization
VISUAL_EXE			= $(addprefix $(VISUAL_DIR),$(VISUAL_EXE_NAME))
VISUAL_COPY			= $(addprefix $(EXE_PATH),$(VISUAL_EXE_NAME))

EXEFILES			= $(addprefix $(EXE_PATH),	$(COREWAR_EXE_NAME) \
												$(CMPDUMP_EXE_NAME) \
												$(VISUAL_EXE_NAME))


all: $(EXE_PATH) $(EXEFILES)

install: make_all all

reinstall: fclean all

make_all:
	@make -C $(COREWAR_DIR) all
	@make -C $(CMPDUMP_DIR) all
	@make -C $(VISUAL_DIR) all

$(EXEDIR):
	@mkdir -p $(EXE_PATH)

# - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - #

corewar: $(COREWAR_COPY)

$(COREWAR_COPY): $(COREWAR_EXE)
	rm -f $(COREWAR_COPY)
	cp $(COREWAR_EXE) $(COREWAR_COPY)

$(COREWAR_EXE):
	@make -C $(COREWAR_DIR)

# - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - #

visualization: $(CMPDUMP_COPY)

$(CMPDUMP_COPY): $(CMPDUMP_EXE)
	rm -f $(CMPDUMP_COPY)
	cp $(CMPDUMP_EXE) $(CMPDUMP_COPY)

$(CMPDUMP_EXE):
	@make -C $(CMPDUMP_DIR)

# - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - #

compare_dumps: $(VISUAL_COPY)

$(VISUAL_COPY): $(VISUAL_EXE)
	rm -f $(VISUAL_COPY)
	cp $(VISUAL_EXE) $(VISUAL_COPY)

$(VISUAL_EXE):
	@make -C $(VISUAL_DIR)

# - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - #

clean:
	rm -f $(EXEFILES)

fclean: clean
	@make -C $(COREWAR_DIR) fclean
	@make -C $(CMPDUMP_DIR) fclean
	@make -C $(VISUAL_DIR) fclean

.PHONY: all install reinstall make_all corewar visualization compare_dumps \
	clean fclean