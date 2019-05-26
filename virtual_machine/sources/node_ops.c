
#include "virtual_machine.h"

void		start_node(uint8_t *addr, int player)
{
	t_process	*new;

	new = NULL;
	if (!(new = malloc(sizeof(t_process))))
		ft_error(ERR_ALLOC);
	new->addr = addr;
	new->reg[0] = player * -1;
}

void		push_node(t_process **root, t_process *new)
{

}
