/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 07:12:07 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/10 14:38:43 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_LIST_H
# define LIBFT_FT_LIST_H

# include <stddef.h>

typedef struct	s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}				t_list;

void			ft_lstadd(t_list **alst, t_list *new);

void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_list			*ft_lstnew(void const *content, size_t content_size);

t_list			*ft_lstrev(t_list **alst);

size_t			ft_lstlen(t_list *lst);

void			ft_lstforeach(t_list *lst, void (*f)(void *, size_t));

t_list			*ft_lstcpy_elem(t_list *list);

int				ft_lstadd_back(t_list **alst, t_list *new);

t_list			*ft_lstcpy(t_list *lst);

t_list			*ft_lstrcpy(t_list *lst);

t_list			*ft_lstsort(t_list *list, int (*f)(t_list *, t_list *));

void			ft_lstswap(t_list *a, t_list *b);

#endif
