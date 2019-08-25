
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
												$(CMPDUMP_EXE_NAME))
#												$(VISUAL_EXE_NAME)

ASSETS_NAME			= champs
ASSETS_DIR			= ./original_sources/
ASSETS_PATH			= $(addprefix $(ASSETS_DIR),$(ASSETS_NAME))
ASSETS_LNK			= $(addprefix $(EXE_PATH),$(ASSETS_NAME))

all: corewar compare_dumps $(ASSETS_LNK)

install: make_all all

reinstall: fclean all

make_all:
	make -C $(COREWAR_DIR) all
	make -C $(CMPDUMP_DIR) all
#	@makebuild -C $(VISUAL_DIR) all

$(EXE_PATH):
	mkdir -p $(EXE_PATH)

$(ASSETS_LNK):
	rm -f $(ASSETS_LNK)
	ln -s $(ASSETS_PATH) $(ASSETS_LNK)

# - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - #

corewar:
	@make -C $(COREWAR_DIR)
	rm -f $(COREWAR_COPY)
	cp $(COREWAR_EXE) $(COREWAR_COPY)


# - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - #

compare_dumps:
	@make -C $(CMPDUMP_DIR)
	rm -f $(CMPDUMP_COPY)
	cp $(CMPDUMP_EXE) $(CMPDUMP_COPY)


# - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - #

visualization: $(VISUAL_COPY)

$(VISUAL_COPY): $(VISUAL_EXE)
	rm -f $(VISUAL_COPY)
	cp $(VISUAL_EXE) $(VISUAL_COPY)

$(VISUAL_EXE):
	@make -C $(VISUAL_DIR)

# - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - #

clean:
	rm -f $(EXEFILES)
	rm -f $(ASSETS_LNK)

fclean: clean
	@make -C $(COREWAR_DIR) fclean
	@make -C $(CMPDUMP_DIR) fclean
#	@makebuild -C $(VISUAL_DIR) fclean

Name = "John"
export Name
testt:
	@make -C executable
	@echo "$(Name)"

.PHONY: all install reinstall make_all corewar visualization compare_dumps \
	clean fclean