/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_dumps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 05:08:13 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/07 16:22:16 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compare_dumps.h"

t_dump		*init_structs()
{
	t_dump	*dd;

	dd = NULL;
	if (!(dd = (t_dump *)malloc(sizeof(t_dump))))
		ft_error("Memory allocated error\n", __func__);
	if (!(dd->strings = (t_output *)malloc(sizeof(t_output))))
		ft_error("Memory allocated error\n", __func__);
	dd->origin_vm = NULL;
	dd->our_vm = NULL;
	dd->strings->origin = NULL;
	dd->strings->our = NULL;
	return (dd);
}

void		free_args(t_dump *dd)
{
	free(dd->strings->origin);
	free(dd->strings->our);
	free(dd->strings);
	free(dd);
}

int 		main(int ac, char *av[])
{
	t_dump	*dd;

	if (ac == 4)
	{
		dd = init_structs();
		read_processes_output(dd, av);
		compare_output(dd);
		free_args(dd);
	}
	else
		ft_error("invalide arguments\n", __func__);
	return (0);
}