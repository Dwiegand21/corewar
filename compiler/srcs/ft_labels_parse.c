/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_labels_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 21:33:13 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/27 21:33:13 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char				*ft_get_lbl_name(t_champ *champ, char **s, char *stop_chars)
{
	char			*str;
	t_string		*res;
	char			*bad_char;

	bad_char = 0;
	if (!s || !*s || !(res = ft_make_string(8)))
		return (0);
	while (!ft_strchr(stop_chars, **s) && !ft_isspace(**s) && **s)
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
		ft_make_error(WRONG_CHAR_LBL, champ,
				(int)(size_t)(bad_char - champ->curr_ln) + 1,
					(void*[4]){bad_char, str, 0, 0});
	return (str);
}

void				ft_upd_labels(t_champ *champ)
{
	int		i;
	int		to;
	void	**map_val;

	i = -1;
	to = champ->current_labels->len;
	while (++i < to)
	{
		if (champ->current_labels->data[i])
		{
			if (!(map_val = ft_map_get(champ->labels,
				champ->current_labels->data[i])))
				exit(ft_free_champ(&champ, 666));
			*map_val = (void*)(size_t)champ->address;
		}
	}
	champ->current_labels->len = 0;
}

void				ft_add_label(t_champ *champ, char *lbl)
{
	void **map_val;

	if (!(map_val = ft_map_get(champ->labels, lbl)))
		exit(ft_free_champ(&champ, 666));
	*map_val = (void*)(size_t)-1;
	if (!ft_vector_push_back(&champ->current_labels, lbl))
		exit(ft_free_champ(&champ, 666));
}

void				ft_parse_label(t_champ *champ, char *ln)
{
	char	*label;
	int		cmd;

	cmd = 0;
	label = ft_get_lbl_name(champ, &ln,
			(char[4]){COMMENT_CHAR, LABEL_CHAR, ALT_CMT_CHAR, '\0'});
	ft_skip_spaces(&ln);
	if (*ln != LABEL_CHAR)
		ft_make_error(MISS_LBL_CHAR, champ,
				(int)(size_t)(ln - champ->curr_ln) + 1,
				(void*[4]){(void*)(size_t)LABEL_CHAR, label, 0, 0});
	ft_add_label(champ, label);
	ln += (*ln && *ln == LABEL_CHAR);
	ft_skip_spaces(&ln);
	if (*ln && *ln != COMMENT_CHAR && *ln != ALT_CMT_CHAR
		&& (cmd = ft_is_command(ln)) >= 0)
		ft_parse_command(champ, ln, cmd);
	else if (cmd == -1)
		ft_make_error(BAD_CMD, champ,
				(int)(size_t)(ln - champ->curr_ln) + 1,
					(void*[4]){(void*)ft_find_bad_cmd_len(ln), ln, 0, 0});
}

int					ft_is_lbl(char *ln, t_champ *champ, int is_cmd, int pos)
{
	static int	name_cmd_len = -1;
	static int	comm_cmd_len = -1;
	int			cm_err;

	cm_err = 0;
	if (name_cmd_len == -1 || comm_cmd_len == -1)
	{
		name_cmd_len = ft_strlen(NAME_CMD_STRING);
		comm_cmd_len = ft_strlen(COMMENT_CMD_STRING);
	}
	if (!is_cmd)
	{
		if (!ft_strncmp(ln, NAME_CMD_STRING, name_cmd_len) ||
			(!ft_strncmp(ln, COMMENT_CMD_STRING, comm_cmd_len) && (cm_err = 1)))
		{
			ft_make_error(NM_CMD_WRONG_PLACE, champ, pos,
						(void*[4]){!cm_err ? "name" : "comment", 0, 0, 0});
			return (0);
		}
		return (1);
	}
	while (ft_strchr(LABEL_CHARS, *ln) && *ln)
		++ln;
	return (*ln == LABEL_CHAR ? 1 : 0);
}
