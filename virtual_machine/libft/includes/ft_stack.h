/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 07:37:34 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/09 09:05:08 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_STACK_H
# define LIBFT_FT_STACK_H

# define ERRSTACK_EMPTY			"Stack is empty"
# define ERRSTACK_FULL			"Stack is full"

typedef struct	s_stckprvt
{
	int				*stack;
	int				*last;
	int				top;
	int				s;
}				t_stckprvt;

typedef struct	s_stack
{
	void	*prvt;
	int		(*pop)(struct s_stack *a);
	void	(*push)(struct s_stack *a, int param);
	int		(*size)(struct s_stack *a);
	int		(*print)(struct s_stack *a);
}				t_stack;

t_stack			*stack_create(int size);
int				stack_delete(t_stack **a);

#endif
