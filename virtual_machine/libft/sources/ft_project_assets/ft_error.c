/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 08:09:25 by axtazy            #+#    #+#             */
/*   Updated: 2019/07/04 16:56:43 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_project_assets.h"
#include "ft_iostream.h"

void		ft_error(char const *restrict error_line,
						char const *restrict function_name)
{
	if (function_name == NULL)
		ft_error(ERRNULLP, __func__);
	ft_putstr_fd(function_name, 2);
	write(2, ": ", 2);
	if (error_line != NULL)
	{
		ft_putendl_fd(error_line, 2);
	}
	exit(1);
}
