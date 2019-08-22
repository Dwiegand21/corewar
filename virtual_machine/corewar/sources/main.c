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

void				help(void)
{
	printf("%s", g_usage);
}

static inline int	ft_make_vectors_for_timelime(
		t_vm_vector_int time[TIMELINE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TIMELINE_SIZE)
		ft_init_vm_vector_int(&time[i], INIT_VECTOR_SIZE);
	return (1);
}

int32_t				main(int argc, char **argv)
{
	t_area			*area;
	t_vm_vector_int	time[TIMELINE_SIZE];

	ft_make_vectors_for_timelime(time);
	if (!ft_init_vm_vector_int(&g_sort_buffer, INIT_SORT_BUF_SIZE))
		ft_error(ERRALLOC, __func__);
	if (!ft_init_vm_vector_rng(&g_sort_ranges, INIT_SORT_RANGES_COUNT))
		ft_error(ERRALLOC, __func__);
	if (argc == 1)
		help();
	else
	{
		area = initialization_area();
		area->time = time;
		read_arguments(area, argc - 1, argv + 1);
		play_game(area);
	}
	return (0);
}
