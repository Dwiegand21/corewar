/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:26:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/05/26 18:26:37 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t 		check_dupm_flag(int32_t* argc, char*** argv, int32_t *dump)
{
	if (ft_strcmp(**argv, "-dump") != 0)
		return (0);
	if (*argc - 1 <= 0)
		ft_error(INV_ARGS);
	(*argc)--;
	(*argv)++;
	if (!is_integer(**argv, dump))
		ft_error(INV_ARGS);
	if (*dump < 0)
		ft_error(INV_ARGS);
	(*argc)--;
	(*argv)++;
	return (1);
}

int32_t 		is_integer(const char *str, int32_t* nbr)
{
	int32_t 	sign;

	sign = 0;
	(*nbr) = 0;
	if (*str == '-')
	{
		sign = 1;
		str++;
	}
	while(*str && *str >= '0' && *str<= '9')
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
	int32_t 	flags;

	flags = 0;
	while (*argc > 0)
	{
		if (check_dupm_flag(argc, argv, dump))
			flags |= DUMP;
		else if (strcmp(*(*argv), "-v") == 0)
			flags |= VISUALIZATION;
		else
			break ;
		(*argc)--;
		(*argv)++;
	}
	return (flags);
}
