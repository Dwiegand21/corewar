CHAMP_NAME = gg

CHAMP_NAME_BYTE = $(addsuffix .cor,$(CHAMP_NAME))

all: call_makes asm corewar $(CHAMP_NAME_BYTE)

################################### COMPILE ####################################
call_makes:
	@$(MAKE) -C compiler
	@$(MAKE) -C virtual_machine
	@$(MAKE) -C champion

asm: compiler/asm
	@cp compiler/asm ./

compiler/asm:
	@$(MAKE) -C compiler

corewar: virtual_machine/corewar
	@cp virtual_machine/corewar ./

virtual_machine/corewar:
	@$(MAKE) -C virtual_machine

$(CHAMP_NAME_BYTE): champion/$(CHAMP_NAME_BYTE)
	@cp champion/$(CHAMP_NAME_BYTE) ./

champion/$(CHAMP_NAME_BYTE):
	@$(MAKE) -C champion

#################################### CLEAN #####################################
clean:
	@$(MAKE) -C compiler clean
	@$(MAKE) -C virtual_machine clean
	@$(MAKE) -C champion clean

fclean:
	@$(MAKE) -C compiler fclean
	@$(MAKE) -C virtual_machine fclean
	@$(MAKE) -C champion fclean
	@rm -f asm
	@rm -f corewar
	@rm -f $(CHAMP_NAME_BYTE)

re: fclean all