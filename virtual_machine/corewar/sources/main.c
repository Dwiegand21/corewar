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

t_vm_vector_int *buffer = 0;

void		help()
{
	printf("%s", USAGE);
}


int			ft_make_vectors_for_timelime(t_vm_vector_int time[TIMELINE_SIZE + 1])
{
	int			i;
	const int	count = TIMELINE_SIZE + 1;

	i = -1;
	while (++i < count)
	{
		ft_init_vm_vector_int(&time[i], INIT_VECTOR_SIZE); // todo remove freeshing vector structure
	}
	return (1); // todo protect
}


int32_t		main(int argc, char **argv)
{
	t_area			*area;
	t_vm_vector_int	time[TIMELINE_SIZE + 1];

	ft_make_vectors_for_timelime(time);
	buffer = ft_make_vm_vector_int(INIT_SORT_BUF_SIZE); // todo protect

	//ft_timsort_test();
	//return (0);

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
//	size_t memory_used = 0;
//	for (int e = 0 ; e < TIMELINE_SIZE + 1; ++e)
//	{
//		memory_used += time[e].capacity * sizeof(int);
//	}
//	memory_used += area->carriages->capacity * sizeof(t_process);
//	printf("Total memory used %zu bytes (%f megabytes)\n", memory_used, memory_used / 1000000.);
	return 0;
}
