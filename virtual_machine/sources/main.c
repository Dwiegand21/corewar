/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:45:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/08/28 15:56:17 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				help(void)
{
	ft_printf("%s", g_usage);
}

static inline int	ft_make_vectors_for_timelime(
		t_vm_vector_int time[TIMELINE_SIZE])
{
	int32_t		i;

	i = 0;
	while (i < TIMELINE_SIZE)
	{
		if (!ft_init_vm_vector_int(&time[i], INIT_VECTOR_SIZE))
			return (0);
		i++;
	}
	return (1);
}

int32_t				main(int argc, char **argv)
{
	t_area			*area;
	t_vm_vector_int	time[TIMELINE_SIZE];

	if (argc == 1)
		help();
	else
	{
		area = initialization_area();
		ft_make_vectors_for_timelime(time);
		area->time = time;
		read_arguments(area, argc - 1, argv + 1);
		if (!ft_init_vm_vector_rng())
			ERRF(ERRALLOC);
		if (!ft_init_vm_vector_int(&g_sort_buffer, INIT_SORT_BUF_SIZE))
			ERRF(ERRALLOC);
		play_game(area);
	}
	return (0);
}
