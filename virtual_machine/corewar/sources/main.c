/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:45:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/07/04 17:50:40 by dwiegand         ###   ########.fr       */
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
	t_process	*time[TIMELINE_SIZE + 1] = { 0 };

	area = NULL;
	if (argc == 1)
	{
		help();
	}
	else
	{
		area = initialization_area();
		area->time = time;
		read_arguments(area, argc - 1, argv + 1);
		play_game(area);
	}
	return 0;
}
