/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:29:55 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/24 12:31:50 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

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

void			ft_error(char *error, int size);
void			ft_putchar(char c);
void			ft_putnbr(int nbr);

#endif
