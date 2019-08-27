/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/24 02:20:20 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t		check_filename(t_cor_file *file, char *filename, bool valid)
{
	if (valid == false)
		ERRF("Program run with invalid arguments:\n"
			"After the ordinal number"
			"the name of champion should follow\n");
	if (ft_strnequ_rev(filename, ".cor", 4) != 0)
	{
		file->file_name = filename;
	}
	else
		ERRF("File with name \'%s\' is invalid:\n"
			"Champion file must have \'.cor\' extension\n");
	return (0);
}

int32_t		fix_ordinal_numbers(t_cor_file *files, int32_t n_players)
{
	int32_t		i;
	int32_t		j;
	int32_t		ordinal_n;

	i = 0;
	ordinal_n = 1;
	while (i < n_players)
	{
		if (files[i].champ_index < 1)
		{
			j = 0;
			while (j < n_players)
			{
				if (ordinal_n == files[j].champ_index)
				{
					j = 0;
					ordinal_n++;
				}
				j++;
			}
			files[i].champ_index = ordinal_n++;
		}
		i++;
	}
	return (0);
}

int32_t		check_numeric_flag(char **argv, int32_t *champ_i, bool next2args)
{
	if (ft_strcmp(*argv, "-n") != 0)
		return (0);
	else
	{
		if (next2args == false)
			ERRF("Program run with invalid arguments:\n"
				"After the \'-n\' flag two more arguments should be\n"
				"./corewar [-d N] [[-n N] filename.cor] ...\n");
		if (!is_integer(*(argv + 1), champ_i))
			ERRF("Program run with invalid arguments:\n"
				"Argument \'%s\' must be a number\n", *(argv + 1));
		if (*champ_i < 0)
			ERRF("Program run with invalid arguments"
				"Champion cannot have a negative ordinal number\n");
	}
	return (2);
}

int32_t		read_arguments(t_area *area, int32_t argc, char **argv)
{
	int32_t		i;
	t_cor_file	files[4];

	area->flags = check_flags(&argc, &argv, &SDUMP_CYCLE);
	i = 0;
	if (argc == 0)
		ERRF("Program run with invalid arguments:\n"
			"There must be at least one champion in the game.\n");
	while (i < argc)
	{
		files[SN_PLAYERS].champ_index = -1;
		i += check_numeric_flag(argv + i,
					&files[SN_PLAYERS].champ_index, i + 2 < argc);
		if (SN_PLAYERS < 4)
			check_filename(files + SN_PLAYERS, argv[i], i < argc);
		else
			ERRF("Program run with invalid arguments:\n"
				"A maximum of 4 champions can participate in one game\n");
		SN_PLAYERS++;
		i++;
	}
	fix_ordinal_numbers(files, SN_PLAYERS);
	initialization_players(area, files);
	return (0);
}
