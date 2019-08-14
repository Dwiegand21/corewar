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


int			ft_make_vectors_for_timelime(t_process *time[TIMELINE_SIZE + 1])
{
	int			i;
	const int	count = TIMELINE_SIZE + 1;

	i = -1;
	while (++i < count)
	{
		time[i] = ft_make_vm_vector_int(INIT_VECTOR_SIZE);
	}
}


int32_t		main(int argc, char **argv)
{
	t_area		*area;
	t_process	*time[TIMELINE_SIZE + 1] = { 0 };


	t_vm_vector_int *v = ft_make_vm_vector_int(0);

	for (int e = 0; e < 100000; ++e)
	{
		ft_vm_vector_int_push_back(&v, e);
	}
	printf("Vector size is %d, capac %d\n", v->len, v->capacity);

	ft_free_vm_vector_int(&v);

	return (0);

	ft_timsort_test();
	exit(0);

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
