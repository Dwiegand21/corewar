/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_vector_rng.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 19:48:55 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/28 14:39:18 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <virtual_machine.h>
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
		ERRF(ERRALLOC);
	ft_memcpy(new_data, old_data, prev_size * sizeof(t_timsort_rng));
	free(old_data);
	return (new_data);
}

int32_t				ft_init_vm_vector_rng(void)
{
	t_vm_vector_rng		*v;

	v = &g_sort_ranges;
	v->len = 0;
	v->offset = 0;
	// todo ??
	v->capacity = INIT_SORT_RANGES_COUNT <= 1 ? 2 : INIT_SORT_RANGES_COUNT;
	v->data = (t_timsort_rng*)malloc(sizeof(t_timsort_rng) * (v->capacity));
	if (!v->data)
	{
		free(v);
		return (0);
	}
	return (1);
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
