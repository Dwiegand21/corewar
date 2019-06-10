/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_project_name_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 05:50:36 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/09 14:08:22 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_project_assets.h"

int			ft_project_assets_init(char const *project_name, unsigned int flags)
{
	int 	length;

	length = 0;
	if (project_name == NULL || (flags & PA_DPROJ) == 0)
		return (-1);
	while (project_name[length])
		length++;
	if (length > 30)
		return (-1);
	while (length >= 0)
	{
		g_project_name[length] = project_name[length];
		length--;
	}
	g_project_status_flags = flags;
	return (0);
}