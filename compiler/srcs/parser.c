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
	char 			*bad_char;

	bad_char = 0;
	if (!s || !*s || !(res = ft_make_string(8)))
		return (0);
	while (**s != LABEL_CHAR && !ft_isspace(**s) && **s)
	{
		if (!ft_strchr(LABEL_CHARS, **s))
			bad_char = bad_char ? bad_char : *s;
		if (!ft_string_push_back(&res, **s))
			exit(ft_free_champ(&champ, 13));
		++(*s);
	}
	str = res->data;
	free(res);
	if (bad_char)
		ft_make_error(WRONG_CHAR_LBL, champ, bad_char - champ->curr_line + 1,
					  (void*[4]){bad_char, str, 0, 0});
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

void 		ft_parse_command(t_champ *champ, char *ln, int cmd)
{
	ln += g_functions[cmd].namelen;

}

size_t		ft_find_bad_cmd_len(char *ln)
{
	size_t len;

	len = 0;
	while (*ln && *ln != SEPARATOR_CHAR && !ft_isspace(*ln))
	{
		++ln;
		++len;
	}
	return (len);
}

void 		ft_add_label(t_champ *champ, char *lbl, char *ln)
{
	void **map_val;
	if (!(map_val = ft_map_get(champ->labels, lbl)))
		exit(ft_free_champ(&champ, 666));
	if (*map_val != champ->labels->nil)
	{
		ft_make_error(MULT_LABEL, champ,
			(int)(ln - ft_strlen(lbl) - (size_t)champ->curr_line + 1),
			(void *[4]){lbl, 0, 0, 0});
		free(lbl);
	}
	else
		*map_val = (void*)(size_t)-1;
	if (!ft_vector_push_back(&champ->current_labels, lbl))
		exit(ft_free_champ(&champ, 666));
}

void 		ft_parse_label(t_champ *champ, char *ln)
{
	char	*label;
	int 	cmd;

	label = ft_get_lbl_name(champ, &ln);
	while (ft_isspace(*ln))
		++ln;
	if (*ln != LABEL_CHAR)
		ft_make_error(MISS_LBL_CHAR, champ, ln - champ->curr_line + 1,
					  (void*[4]){(void*)(size_t)LABEL_CHAR, label, 0, 0});
	ft_add_label(champ, label, ln);
	ln += (*ln && *ln == LABEL_CHAR);
	while (ft_isspace(*ln))
		++ln;
	if (*ln && (cmd = ft_is_command(ln)) >= 0)
		ft_parse_command(champ, ln, cmd);
	else if (*ln)
		ft_make_error(BAD_CMD, champ, ln - champ->curr_line + 1,
					  (void*[4]){(void*)ft_find_bad_cmd_len(ln), ln, 0, 0});
}

void 		ft_parse_line(t_champ *champ, char *ln)
{
	int cmd;

	if (!*ln)
		return ;
	while (ft_isspace(*ln))
		++ln;
	if (*ln == COMMENT_CHAR)
		return ;
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
		ft_parse_line(champ, ln);
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
	ft_parse_exec(champ, fd);

	ft_printf("<%s>\n", champ->name->data);
	ft_printf("<%s>\n", champ->comment->data);
	ft_printf("<%s>\n", champ->curr_line);



	return (champ);
}

