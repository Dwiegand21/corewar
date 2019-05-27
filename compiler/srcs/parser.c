/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:44:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/25 19:44:22 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_get_lbl_name(t_champ *champ, char **s)
{
	char			*str;
	t_string		*res;

	// todo stop in space. Raise error about wrong char in label

	if (!s || !*s)
		return (0);
	if (!(res = ft_make_string(8)))
		return (0);
	while (**s != LABEL_CHAR && **s)
	{
		if (!ft_strchr(LABEL_CHARS, **s))
		{
			ft_free_string(&res);
			return (0);
		}
		if (!ft_string_push_back(&res, **s))
			exit(ft_free_champ(&champ, 13));
		++(*s);
	}
	str = res->data;
	free(res);
	return (str);
}

int 		ft_is_command(char *line)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		if (!ft_strncmp(line, g_functions[i].name, g_functions[i].namelen))
		{
			return (i);
		}
	}
	return (-1);
}

void 		ft_parse_label(t_champ *champ, char *ln)
{
	char *label;

	if (!(label = ft_get_lbl_name(champ, &ln)))
	{
		ft_make_error(MULT_LABEL, champ, (void*[4]){}) // todo error - wrong char in label
		return ;
	}
}

void 		ft_parse_command(t_champ *champ, char *ln, int cmd)
{
	ln += g_functions[cmd].namelen;

}

void 		ft_parse_line(t_champ *champ, char *ln)
{
	int cmd;

	if (!*ln)
		return ;
	while (ft_isspace(*ln))
		++ln;
	if ((cmd = ft_is_command(ln)) >= 0)
		ft_parse_command(champ, ln, cmd);
	else
		ft_parse_label(champ, ln);

}

void 		ft_parse_exec(t_champ *champ, int fd)
{
	char *ln;

	ft_parse_line(champ, champ->curr_line);
	while ((ln = (void*)1lu) && ft_get_next_line(fd, &ln, BUFF_SIZE) &&
		   ++champ->line)
	{
		if (!ln)
			exit(ft_free_champ(&champ, 13));
		ft_champ_upd_line(champ, ln);
	}
}

t_champ 	*ft_parser(char *file)
{
	t_champ *champ;
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1) // todo check extension
		return (0);
	if (!(champ = ft_make_champ(file, fd)))
		return (0);
	ft_parse_header(champ, fd);

	ft_printf("<%s>\n", champ->name->data);
	ft_printf("<%s>\n", champ->comment->data);
	ft_printf("<%s>\n", champ->curr_line);



	return (champ);
}

