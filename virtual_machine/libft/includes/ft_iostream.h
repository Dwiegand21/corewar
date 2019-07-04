/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iostream.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 06:43:41 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/11 01:57:19 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_IOSTREAM_H
# define LIBFT_FT_IOSTREAM_H

# include <unistd.h>

# define GNL_BUFF_SIZE 512
# define MAX_SIZE_FD 20

typedef struct s_list		t_list;

int				ft_get_lines_to_lst(int fd, t_list **list);

int				ft_get_next_line(const int fd, char **line);

void			ft_putchar_fd(char c, int fd);

void			ft_putchar(char c);

void			ft_putendl_fd(char const *s, int fd);

void			ft_putendl(char const *s);

void			ft_putnbr_fd(int n, int fd);

void			ft_putnbr(int n);

void			ft_putstr_fd(char const *s, int fd);

void			ft_putstr(char const *s);

#endif
