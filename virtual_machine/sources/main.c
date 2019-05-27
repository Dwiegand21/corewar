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


int32_t		main(int argc, char** argv)
{
	t_area*		area;

	area = NULL;
	if (argc == 1)
	{
		help();
	}
	else
	{
		area = initialization_area();
		read_arguments(area, argc - 1, argv + 1);
	}

	free_args(&area);
	return 0;
}