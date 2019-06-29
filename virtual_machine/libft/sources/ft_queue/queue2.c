/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:34:41 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/28 13:53:03 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"
#include <stdlib.h>

int				queue_delete(t_queue **p)
{
	if (p && *p)
	{
		free(((t_qeueprvt *)((*p)->prvt))->que);
		((t_qeueprvt *)((*p)->prvt))->que = NULL;
		free(((t_qeueprvt *)((*p)->prvt)));
		((*p)->prvt) = NULL;
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
