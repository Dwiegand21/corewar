/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 09:03:17 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/26 09:03:17 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_parse_header(t_champ *champ, int fd)
{
	char *ln;

	while ((ln = (void*)1lu) && ft_get_next_line(fd, &ln, BUFF_SIZE) &&
										++champ->line)
	{
		if (!ln)
			exit(ft_free_champ(&champ, 13));
		ft_champ_upd_line(champ, ln);
		ft_skip_spaces(&ln);
		if (!ft_strncmp(ln, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
			ft_parse_name_comment(champ, ln, COMMENT);
		else if (!ft_strncmp(ln, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			ft_parse_name_comment(champ, ln, NAME);
		else if (ln[0] && ln[0] != COMMENT_CHAR && ln[0] != ALT_CMT_CHAR)
			return (ft_check_exist_name_cmt(champ));
	}
	ft_check_exist_name_cmt(champ);
}

void		ft_parse_name_comment(t_champ *champ, char *ln, t_token_type type)
{
	int ignore;

	ignore = 0;
	if ((type == NAME ? champ->name->offset : champ->comment->offset) == 1)
	{
		ft_printf(g_is_silent ? "" : g_wrn_double,
				type == NAME ? "name" : "comment");
		ft_printf(g_is_silent ? "" : g_pos,
				champ->file, champ->line, 0);
		ignore = 1;
	}
	if (type == NAME)
		champ->name->offset = 1;
	else
		champ->comment->offset = 1;
	if (!ft_validate_string(champ, &ln, type))
		return (ft_skip_string(champ, ln));
	if (!ignore)
		ft_parse_string(ln, type == NAME ? &champ->name : &champ->comment,
						type, champ);
	else
		ft_parse_string(ln, 0, type, champ);
}

int			ft_validate_string(t_champ *champ, char **ln, t_token_type type)
{
	int pos;

	pos = type == NAME ? ft_strlen(NAME_CMD_STRING) :
					ft_strlen(COMMENT_CMD_STRING);
	*ln += pos;
	ft_skip_spaces(ln);
	if (**ln != '"' && **ln)
	{
		ft_make_error(UNEXP_TOKEN, champ, *ln - champ->curr_ln + 1,
					(void*[4]){(void*)*ln, (void*)(size_t)'"', 0, 0});
		return (0);
	}
	else if (!**ln)
	{
		ft_make_error(SAME_LINE_EXP, champ, *ln - champ->curr_ln + 1,
		(void*[4]){(type == NAME ? (void*)"name" : (void*)"comment"), 0, 0, 0});
		return (0);
	}
	*ln += **ln == '"';
	return (1);
}

void		ft_parse_string(char *ln, t_string **res, t_token_type type,
		t_champ *champ)
{
	if (!ft_get_data_from_line(ln, res, type, champ))
	{
		while ((ln = (void*)1lu) &&
				ft_get_next_line(champ->fd, &ln, BUFF_SIZE) && ++champ->line)
		{
			if (!ln)
				exit(ft_free_champ(&champ, 13));
			if (!ft_string_push_back(res, '\n'))
				exit(ft_free_champ(&champ, 666));
			ft_champ_upd_line(champ, ln);
			if (ft_get_data_from_line(ln, res, type, champ))
				break ;
		}
	}
}

int			ft_get_data_from_line(char *ln, t_string **res, t_token_type type,
		t_champ *chmp)
{
	const size_t	max_len = ft_get_max_len(type);
	static int		name_warning = 0;
	static int		comment_warning = 0;

	--ln;
	while (*++ln && *ln != COMMENT_CHAR && *ln != ALT_CMT_CHAR) // todo need ??
	{
		if (*ln != '"' && (!res || (*res)->len <= max_len))
		{
			if (*ln != '\\')
			{
				if (!ft_string_push_back(res, *ln))
					exit(ft_free_champ(&chmp, 666));
			}
			else if (++ln)
				ft_parse_backslash(&ln, res, chmp);
		}
		else if (*ln != '"' && (*res)->len > max_len &&
			(type == NAME ? name_warning++ : comment_warning++) == 0 &&
			ft_printf(FRMT(g_wrn_too_long), type == NAME ? "name" : "comment"))
			ft_printf(FRMT(g_pos), chmp->file, chmp->line, ln - chmp->curr_ln);
		if (*ln == '"' && *(ln - 1) != '\\')
			return (ft_check_empty_string(ln, chmp, type));
	}
	return (0);
}
