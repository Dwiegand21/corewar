CHAMP_NAME = gg

ASM = asm
VM = corewar
CHAMP = $(addsuffix .cor,$(CHAMP_NAME))

all: $(ASM) $(VM) $(CHAMP)

################################### COMPILE ####################################

$(ASM): compiler/asm
	@cp compiler/asm ./

compiler/asm:
	@$(MAKE) -C compiler

$(VM): virtual_machine/corewar
	@cp virtual_machine/corewar ./

virtual_machine/corewar:
	@$(MAKE) -C virtual_machine

$(CHAMP): champion/$(CHAMP)
	@cp champion/$(CHAMP) ./

champion/$(CHAMP):
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
	@rm -f $(CHAMP)

re: fclean all