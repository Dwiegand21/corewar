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
#include <time.h>

t_vm_vector_int *buffer = 0;
long timeout_time;

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
	t_area          *area;
	t_vm_vector_int timeline[TIMELINE_SIZE + 1];

	ft_make_vectors_for_timelime(timeline);
	buffer = ft_make_vm_vector_int(INIT_SORT_BUF_SIZE); // todo protect

	area = initialization_area();
	area->time = timeline;
	timeout_time = time(0) + atoi(argv[1]);
	read_arguments(area, argc - 2, argv + 2);
	play_game(area);



	return 0;
}
