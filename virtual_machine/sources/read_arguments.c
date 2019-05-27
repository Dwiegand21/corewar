/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:25:12 by axtazy            #+#    #+#             */
/*   Updated: 2019/05/26 18:25:12 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t			check_filename(t_cor_file* file, char* filename, bool valid)
{
	if (valid == false)
		ft_error(INV_ARGS);
	if (ft_strnequ_rev(filename, ".cor", 4) != 0)
	{
		file->file_name = filename;

#if defined DEBUG_
		printf("%d: %s\n",
			   file->champ_index,
			   file->file_name);
#endif // DEBUG_

	}
	else
		ft_error(INV_ARGS);
	return (0);
}

int32_t			fix_ordinal_numbers(t_cor_file *files, int32_t n_players)
{
	int32_t 	i;
	int32_t 	j;
	int32_t 	ordinal_n;

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
}

int32_t 		check_numeric_flag(char **argv, int32_t* champ_i, bool next2args)
{
	if (ft_strcmp(*argv, "-n") != 0)
		return (0);
	else
	{
		if (next2args == false)
			ft_error(INV_ARGS);
		if (!is_integer(*(argv + 1), champ_i))
			ft_error(INV_ARGS);
		if (*champ_i < 0)
			ft_error(INV_ARGS);
	}

	return (2);
}

int32_t 		read_arguments(t_area *area, int32_t argc, char **argv)
{
	int32_t 	i;
	t_cor_file	files[4];

	area->flags = check_flags(&argc, &argv, &area->dump_round);
	i = 0;
	while (i < argc)
	{
		files[area->n_players].champ_index = -1;
		i += check_numeric_flag(argv + i,
								&files[area->n_players].champ_index, i + 2 < argc);
		if (area->n_players < 4)
			check_filename(files + area->n_players, argv[i], i < argc);
		else
			ft_error(ERR_MANY_ARGS);
		area->n_players++;
		i++;
	}
	fix_ordinal_numbers(files, area->n_players);
	initialization_players(area, files);

#if defined DEBUG_
	# ifdef DEBUG_MAP_
	print_map(area->map);
# endif // DEBUG_MAP_
	printf("\n");
	if (area->flags & VISUALIZATION)
		printf("visualization on\n");
	if (area->flags & DUMP)
		printf("dump on\n");
#endif // DEBUG_

}
