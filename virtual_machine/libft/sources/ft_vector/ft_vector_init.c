/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:49:35 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/27 21:26:01 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_vector_func_name.h"
#include "ft_project_assets.h"
#include "ft_memory.h"

t_vector	*vector_init(size_t n)
{
	t_vector	*p;

	p = NULL;
	if ((p = (t_vector *)malloc(sizeof(t_vector))) == NULL)
		ft_error(ERRALLOC, __func__);
	if ((p->data = (struct s_vector_data *)malloc(sizeof(struct s_vector_data)))
			== NULL)
		ft_error(ERRALLOC, __func__);
	((struct s_vector_data*)p->data)->begin = ft_memalloc(sizeof(void *) * n);
	if (((struct s_vector_data*)p->data)->begin == NULL)
		ft_error(ERRALLOC, __func__);
	((struct s_vector_data*)p->data)->size = n;
	((struct s_vector_data*)p->data)->end =
		((struct s_vector_data*)p->data)->begin;
	p->v = ((struct s_vector_data*)p->data)->begin;
	p->begin = &ft_vector_begin;
	p->end = &ft_vector_end;
	p->join = &ft_vector_join;
	p->push_back = &ft_vector_push_back;
	return (p);
}
