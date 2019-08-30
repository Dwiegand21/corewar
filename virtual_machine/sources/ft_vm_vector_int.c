/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_vector_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:09:26 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/14 18:09:26 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vm_vector.h"

static inline int		*ft_realloc_vm(int *old_data, int prev_size,
		int new_size)
{
	int		*new_data;

	if (!old_data)
		return (0);
	new_data = (int*)malloc(new_size * sizeof(int));
	if (!new_data)
		ERRF(ERRALLOC);
	ft_memcpy(new_data, old_data, prev_size * sizeof(int));
	free(old_data);
	return (new_data);
}

t_vm_vector_int			*ft_init_vm_vector_int(t_vm_vector_int *v,
		int init_size)
{
	v->len = 0;
	v->capacity = init_size <= 1 ? 2 : init_size;
	v->data = (int*)malloc(sizeof(int) * (v->capacity));
	if (!v->data)
	{
		free(v);
		return (0);
	}
	v->data[0] = 0;
	return (v);
}

char					ft_vm_vector_int_push_back(t_vm_vector_int *v, int c)
{
	if (v->len == v->capacity - 1)
	{
		v->data = ft_realloc_vm(v->data, v->capacity,
				v->capacity * 2);
		if (!v->data)
		{
			return (0);
		}
		v->capacity *= 2;
	}
	v->data[v->len++] = c;
	v->data[v->len] = 0;
	return (1);
}

char					ft_vm_vector_int_realloc(t_vm_vector_int *v)
{
	v->data = ft_realloc_vm(v->data, v->capacity,
							v->capacity * 2);
	if (!v->data)
	{
		return (0);
	}
	v->capacity *= 2;
	return (1);
}
