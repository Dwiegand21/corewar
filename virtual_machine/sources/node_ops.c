
#include "virtual_machine.h"

t_process*		start_node(uint8_t *addr, int player)
{
	int32_t 	i;
	t_process	*new;

	new = NULL;
	if (!(new = malloc(sizeof(t_process))))
		ft_error(ERR_ALLOC);

	i = 1;
	while (i < REG_SIZE)
	{
		new->reg[i] = 0;
		i++;
	}
	new->addr = addr;
	new->reg[0] = player * -1;

	new->carry = false;
	new->live_in_session = false;

	new->sleep = 0;
	new->player = player;

	new->next = NULL;

	return (new);
}

void		push_node(t_process **root, t_process *new)
{

}
