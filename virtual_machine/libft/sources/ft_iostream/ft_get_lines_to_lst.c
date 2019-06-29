/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_lines_to_lst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 07:27:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/09 09:09:55 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_string.h"
#include "ft_iostream.h"
#include "ft_list.h"
#include "ft_memory.h"

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
		ft_lstdel(list, ft_memclear_n_del);
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

int					ft_get_lines_to_lst(int fd, t_list **list)
{
	char		*buf;
	char		*line;
	int			ret;

	line = NULL;
	if (fd < 0 || !(buf = (char *)malloc(sizeof(char) * GNL_BUFF_SIZE + 1)))
		return (0);
	ret = 1;
	while (ret > 0)
	{
		if ((ret = read(fd, buf, GNL_BUFF_SIZE)) > 0)
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
