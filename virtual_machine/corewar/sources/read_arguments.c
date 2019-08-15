/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/05/27 16:55:36 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t		check_numeric_flag(char **argv, int32_t *champ_i, bool next2args)
{
	if (ft_strcmp(*argv, "-n") != 0)
		return (0);
	else
	{
		if (next2args == false)
			ft_error(ARGINV, __func__);
		if (!is_integer(*(argv + 1), champ_i))
			ft_error(ARGINV, __func__);
		if (*champ_i < 0)
			ft_error(ARGINV, __func__);
	}
	return (2);
}

int32_t		read_arguments(t_area *area, int32_t argc, char **argv)
{
	int32_t		i;
	t_cor_file	files[2];
	int 		champ_idx = -1;

	///area->flags = check_flags(&argc, &argv, &SDUMP_CYCLE);
	i = 0;
	///if (argc == 0)
	///	ft_error(ARGINV, __func__);

	files[0].champ_index = -1;
	files->file_name = argv[0];

	files[1].champ_index = -2;
	(files + 1)->file_name = argv[1];
	SN_PLAYERS = 2;

	initialization_players(area, files);
	return (0);
}

