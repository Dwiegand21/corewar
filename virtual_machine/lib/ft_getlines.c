/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 07:27:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/03/06 05:59:58 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_stc_error(char **buf, char **line, t_list **list)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (buf && *buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (list && *list)
		ft_lstdel(list, ft_memzerdel);
	return (0);
}

static int			ft_fill_line(char **line, char *buf)
{
	char		*new;

	new = NULL;
	if (!(*line))
		*line = ft_strdup(buf);
	else
	{
		new = ft_strjoin(*line, buf);
		free(*line);
		*line = new;
	}
	return (((*line) != NULL));
}

static int			ft_join(char **line, t_list **list)
{
	char		*c;
	char		*mod;

	c = NULL;
	if (!line || !(*line))
		return (0);
	while ((c = ft_strchr(*line, '\n')))
	{
		*c = 0;
		if (*line)
			ft_lstadd_back(list, ft_lstnew(ft_strdup(*line), ft_strlen(*line)));
		mod = ft_strdup(c + 1);
		free(*line);
		*line = mod;
	}
	return (1);
}

int					ft_getlines(int fd, t_list **list)
{
	char		*buf;
	char		*line;
	int			ret;

	line = NULL;
	if (fd < 0 || !(buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (0);
	ret = 1;
	while (ret > 0)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = 0;
			if (ret == -1 || !ft_fill_line(&line, buf) || !ft_join(&line, list))
				return (ft_stc_error(&buf, &line, list));
		}
	}
	if (line && *line)
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(line), ft_strlen(line)));
	}
	if (line)
		free(line);
	return (1);
}
