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

static inline int				*ft_realloc_vm(int *old_data, int prev_size,
								int new_size)
{
	int		*new_data;
	int		i;

	if (!old_data)
		return (0);
	new_data = (int*)malloc(new_size * sizeof(int));
	if (!new_data)
	{
		free(old_data);
		return (0);
	}
	i = 0;
	while (i < prev_size && i < new_size)
	{
		new_data[i] = old_data[i];
		++i;
	}
	free(old_data);
	return (new_data);
}

t_vm_vector_int		*ft_make_vm_vector_int(size_t init_size)
{
	t_vm_vector_int *v;

	v = (t_vm_vector_int*)ft_memalloc(sizeof(t_vm_vector_int) * 1);
	if (!v)
		return (0);
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

char			ft_vm_vector_int_push_back(t_vm_vector_int **v_ptr, int c)
{
	t_vm_vector_int *v;

	if (!v_ptr || !*v_ptr)
		return (-1);
	v = *v_ptr;
	if (v->len == v->capacity - 1)
	{
		v->data = ft_realloc_vm(v->data, v->capacity,
								  v->capacity * 2);
		if (!v->data)
		{
			ft_free_vm_vector_int(v_ptr);
			return (0);
		}
		v->capacity *= 2;
	}
	v->data[v->len++] = c;
	v->data[v->len] = 0;
	return (1);
}