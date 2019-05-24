/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    main.c                                             :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: dwiegand <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 08:22:24 by dwiegand          #+# #+#               */
/*    Updated: 2019/05/24 08:22:24 by dwiegand         ### ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		help()
{
	write(1, "help <<\n", 8);
}


int32_t		main(int av, char** ac)
{
	t_area*		p;


	p = NULL;
	if (av == 1) {
		help();
	} else if (av < 6) {
		initialisation_area(av - 1, ac);
	} else {
		write(2, "corewar: Too many arguments\n", 28);
	}

	return 0;
}