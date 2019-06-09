/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:15:10 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/24 17:08:58 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char		*ft_stock_the_new_line(char *str)
{
	int			i;
	int			len;
	char		*new;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (!(new = (char *)malloc(sizeof(*new) * len + 1)))
		return (NULL);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

static char		*ft_catout_new(char *str)
{
	char		*new;
	int			i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if ((str[i] && !str[i + 1]) || !str[i])
	{
		ft_strdel(&str);
		return (NULL);
	}
	new = ft_strdup(str + i + 1);
	ft_strdel(&str);
	return (new);
}

static char		*join(char *cur, char *new)
{
	char	*res;

	res = ft_strjoin(cur, new);
	if (res && !(*res))
	{
		free(res);
		res = NULL;
	}
	free(cur);
	return (res);
}

int				get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	static char	*new;

	if (BUFF_SIZE < 0 || !line || fd > MAX_SIZE_FD || fd < 0)
		return (-1);
	if (!new)
		new = ft_strnew(1);
	ret = 2;
	while (!(ft_strchr(new, '\n')))
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buff[ret] = '\0';
		if (!(new = join(new, buff)))
			return (0);
		else if (!ret)
			break ;
	}
	*line = ft_stock_the_new_line(new);
	new = ft_catout_new(new);
	return (1);
}
