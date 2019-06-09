/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:33:26 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/24 12:33:55 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include <stdlib.h>

int				stack_delete(t_stack **p)
{
	if (p && *p)
	{
		free(((t_stckprvt *)((*p)->prvt))->stack);
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
