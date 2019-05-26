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
	t_area*		area;

	area = NULL;
	if (av == 1) {
		help();
	} else {
		area = initialization_area();
		read_arguments(area, av - 1, ac + 1);

	}

	if (DISPLAY)
		printf("visualizator!\n");
	free_args(&area);
	return 0;
}