/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/24 02:22:07 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t			check_dupm_flag(int32_t *argc, char ***argv, int32_t *dump)
{
	if (ft_strcmp(**argv, "-d") != 0)
		return (0);
	if (*argc - 1 <= 0)
		ERRF("Program run with invalid arguments:\n"
			 "After the \'-d\' flag one more argument should be\n"
			 "./corewar [-d N] [[-n N] filename.cor] ...\n");
	(*argc)--;
	(*argv)++;
	if (!is_integer(**argv, dump))
		ERRF("Program run with invalid arguments:\n"
				"After the \'-d\' flag"
				"one more argument must be is positive digit\n");
	if (*dump < 0)
		ERRF("Program run with invalid arguments:\n"
			 "After the \'-d\' flag"
			 "one more argument must be is positive digit\n");
	return (1);
}

int32_t			is_integer(const char *str, int32_t *nbr)
{
	int32_t		sign;

	sign = 0;
	(*nbr) = 0;
	if (*str == '-')
	{
		sign = 1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		(*nbr) *= 10;
		(*nbr) += *str - '0';
		str++;
	}
	if (sign)
		(*nbr) = ~(*nbr) + 1;
	return ((*str) ? (0) : (1));
}

int32_t			check_flags(int32_t *argc, char ***argv, int32_t *dump)
{
	int32_t		flags;

	flags = 0;
	while (*argc > 0)
	{
		if (check_dupm_flag(argc, argv, dump))
			flags |= DUMP;
		else if (ft_strcmp(*(*argv), "-v") == 0)
			flags |= VISUALIZATION;
		else if (ft_strcmp(*(*argv), "-p") == 0)
			flags |= PROCESS_PRINT;
		else
			break ;
		(*argc)--;
		(*argv)++;
	}
	return (flags);
}