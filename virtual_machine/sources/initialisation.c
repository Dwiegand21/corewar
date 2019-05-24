/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    initialisation.c                                   :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: dwiegand <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 08:56:22 by dwiegand          #+# #+#               */
/*    Updated: 2019/05/24 08:56:22 by dwiegand         ### ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_area*		initialisation_area(int av, char** ac)
{
	t_area*		new = NULL;

	if (!(new = malloc(sizeof(t_area))))
		write(1, "error\n", 6);

	if (!(new->map = malloc(sizeof(char) * MEM_SIZE)))
		write(1, "error\n", 6);

	new->cycle_to_die = CYCLE_TO_DIE;
	new->cycle_step = 0;
	new->round = 0;
}