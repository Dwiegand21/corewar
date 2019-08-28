/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:10:11 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/28 15:10:11 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int		free_printf(t_env *env)
{
	t_plist *tmp;

	if (env)
	{
		if (env->args)
		{
			if (env->args->arg_list)
				free(env->args->arg_list);
			free(env->args);
		}
		while (env->plist)
		{
			tmp = env->plist->next;
			if (env->plist->prepared)
				free(env->plist->prepared);
			free(env->plist);
			env->plist = tmp;
		}
		free(env);
	}
	return (0);
}
