/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:27:04 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/24 12:34:26 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

typedef struct	s_qeueprvt
{
	int		*que;
	int		*first;
	int		*last;
	int		s;
}				t_qeueprvt;

typedef struct	s_queue
{
	void	*prvt;
	void	(*push)(struct s_queue *a, int param);
	int		(*pop)(struct s_queue *a);
	int		(*size)(struct s_queue *a);
	int		(*print)(struct s_queue *a);
}				t_queue;

t_queue			*queue_create(int size);
int				queue_delete(t_queue **a);

void			ft_error(char *error, int size);
void			ft_putchar(char c);
void			ft_putnbr(int nbr);

#endif
