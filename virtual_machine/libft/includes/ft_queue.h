/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 07:32:29 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/09 07:34:06 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_QUEUE_H
# define LIBFT_FT_QUEUE_H

# define EQ_EMPTY		"Queue is empty"
# define EQ_FULL		"Queue is full"

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

#endif
