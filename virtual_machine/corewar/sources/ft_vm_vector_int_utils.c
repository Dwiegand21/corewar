/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_vector_int_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:29:32 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/14 18:29:32 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vm_vector.h"

static inline void	ft_free_array(void **arr, size_t size,
									void (*free_data)(void*))
{
	size_t i;

	if (!free_data)
		return ;
	i = (size_t)-1;
	while (++i < size)
	{
		free_data(arr[i]);
	}
}

void				ft_free_vm_vector_int_simple(void *v_ptr)
{
	t_vm_vector_int *v;

	v = v_ptr;
	if (!v)
		return ;
	free(v->data);
	free(v);
}

void				ft_free_vm_vector_int(t_vm_vector_int **v)
{
	if (!v)
		return ;
	ft_free_vm_vector_int_simple(*v);
	*v = 0;
}

int					ft_free_ret_vm_vector_int(t_vm_vector_int **v, int ret)
{
	ft_free_vm_vector_int(v);
	return (ret);
}