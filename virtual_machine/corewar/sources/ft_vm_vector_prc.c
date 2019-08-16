/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_vector_prc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:53:49 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/14 18:53:49 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vm_vector.h"

static inline void				*ft_realloc_vm_free(void *old_data, size_t prev_size,
													  size_t new_size)
{
	void	*new_data;
	//size_t	i;

	if (!old_data)
		return (0);
	new_data = malloc(new_size);
	if (!new_data)
	{
		free(old_data);
		ft_error(ERRALLOC, __func__);
		return (0);
	}
	ft_memcpy(new_data, old_data, prev_size);
	free(old_data);
	return (new_data);
}

t_vm_vector_prc		*ft_make_vm_vector_prc(int init_size)
{
	t_vm_vector_prc *v;

	v = (t_vm_vector_prc*)ft_memalloc(sizeof(t_vm_vector_prc));
	if (!v)
		ft_error(ERRALLOC, __func__);
	v->capacity = init_size <= 1 ? 2 : init_size;
	v->data = (t_process*)malloc(sizeof(t_process) * (v->capacity));
	if (!v->data)
	{
		free(v);
		ft_error(ERRALLOC, __func__);
		return (0);
	}
	return (v);
}

t_process			*ft_vm_vector_prc_push_back(t_vm_vector_prc **v_ptr)
{
	t_vm_vector_prc *v;

	if (!v_ptr || !*v_ptr)
		return (0);
	v = *v_ptr;
	if (v->len == v->capacity - 1)
	{
		v->data = ft_realloc_vm_free(v->data, v->capacity * sizeof(t_process),
									 v->capacity * 2 * sizeof(t_process));
		if (!v->data)
		{
			ft_free_vm_vector_prc(v_ptr);
			return (0);
		}
		v->capacity *= 2;
	}
	//v->data[v->len++] = c;
	//v->data[v->len] = 0;
	return (&v->data[v->len++]);
}