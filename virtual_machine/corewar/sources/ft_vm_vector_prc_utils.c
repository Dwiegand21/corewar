/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vm_vector_prc_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 19:13:34 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/14 19:13:34 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_types.h"

void				ft_free_vm_vector_prc_simple(void *v_ptr)
{
	t_vm_vector_prc *v;

	v = v_ptr;
	if (!v)
		return ;
	free(v->data);
	free(v);
}

void				ft_free_vm_vector_prc(t_vm_vector_prc **v)
{
	if (!v)
		return ;
	ft_free_vm_vector_prc_simple(*v);
	*v = 0;
}

int					ft_free_ret_vm_vector_prc(t_vm_vector_prc **v, int ret)
{
	ft_free_vm_vector_prc(v);
	return (ret);
}