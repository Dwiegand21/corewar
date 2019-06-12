/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:45:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/12 12:55:22 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		help()
{
	printf("%s", USAGE);
}


int32_t		main(int argc, char **argv)
{
	t_area		*area;

	area = NULL;
	ft_project_assets_init("corewar", PA_DPROJ | PA_DFUNC);
	if (argc == 1)
	{
		help();
	}
	else
	{
		area = initialization_area();
		read_arguments(area, argc - 1, argv + 1);
//		print_dump(area);
		play_game(area);
	}
	free_args(&area);
	return 0;
}
