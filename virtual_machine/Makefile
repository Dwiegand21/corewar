
COREWAR_DIR			= ./corewar/
COREWAR_EXE_NAME	= corewar
COREWAR_EXE			= $(addprefix $(COREWAR_DIR),$(COREWAR_EXE_NAME))

CMPDUMP_DIR			= ./compare_dumps/
CMPDUMP_EXE_NAME	= dumpcmp
CMPDUMP_EXE			= $(addprefix $(CMPDUMP_DIR),$(CMPDUMP_EXE_NAME))

VISUAL_DIR			= ./visualisation/
VISUAL_EXE_NAME		= visualization
VISUAL_EXE			= $(addprefix $(VISUAL_DIR),$(VISUAL_EXE_NAME))

all: corewar

corewar:
	@make -C $(COREWAR_DIR) 1>/dev/null

visualization:
	@make -C $(VISUAL_DIR) 1>/dev/null

compare_dumps:
	@make -C $(CMPDUMP_DIR) 1>/dev/null

fclean:


.PHONY: corewar visualization compare_dumps