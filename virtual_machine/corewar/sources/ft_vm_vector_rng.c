/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_vector_rng.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 19:48:55 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/21 19:48:55 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vm_vector.h"

static inline t_timsort_rng	*ft_realloc_vm(t_timsort_rng *old_data,
										int prev_size,
										int new_size)
{
	t_timsort_rng	*new_data;

	if (!old_data)
		return (0);
	new_data = (t_timsort_rng*)malloc(new_size * sizeof(t_timsort_rng));
	if (!new_data)
		ft_error(ERRALLOC, __func__);
	ft_memcpy(new_data, old_data, prev_size * sizeof(t_timsort_rng));
	free(old_data);
	return (new_data);
}

t_vm_vector_rng				*ft_init_vm_vector_rng(t_vm_vector_rng *v,
												int init_size)
{
	v->len = 0;
	v->offset = 0;
	v->capacity = init_size <= 1 ? 2 : init_size;
	v->data = (t_timsort_rng*)malloc(sizeof(t_timsort_rng) * (v->capacity));
	if (!v->data)
	{
		free(v);
		return (0);
	}
	return (v);
}

char						ft_vm_vector_rng_realloc(t_vm_vector_rng *v)
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
