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

int 	ft_parse_champ(t_champ *champ) {

	champ = 0;
	return (1);
}

//int 	ft_check_header(t_champ *champ)
//{
//	if (champ->name)
//	{
//
//	}
//	return (1);
//}

int 	ft_validate_string(t_champ *champ, char **ln, t_token_type type)
{
	int pos;

	pos = type == NAME ? ft_strlen(NAME_CMD_STRING) :
		  ft_strlen(COMMENT_CMD_STRING);
	*ln += pos;
	while (**ln && ft_isspace(**ln) && ++pos)
		++(*ln);
	if (**ln != '"' && **ln)
	{
		ft_make_error(UNEXP_TOKEN, champ, pos + 1,
				(void*[4]){(void*)*ln, (void*)(size_t)'"', 0, 0});
		return (0);
	}
	else if (!**ln)
	{
		ft_make_error(SAME_LINE_EXP, champ, pos + 1,
		(void*[4]){(type == NAME ? (void*)"name" : (void*)"comment"), 0, 0, 0});
		return (0);
	}
	*ln += **ln == '"';
	return (1);
}

void 	ft_parse_byte(char **ln, t_string **res, t_champ *champ)
{
	char *tmp;
	char tmp_char;
	char radix;

	radix = (**ln == 'x' || **ln == 'X') ? 16 : 8;
	tmp = *ln;
	if (tmp[1] && tmp[2] && tmp[3] && (tmp_char = tmp[3]))
		tmp[3] = '#';
	(*ln) += (radix == 16);
	if (!ft_string_push_back(res, (char)ft_atoi_base_m_non_trim(ln, radix)))
		exit(ft_free_champ(&champ, 666));
	if (tmp[1] && tmp[2] && tmp[3])
		tmp[3] = tmp_char;
	if (radix == 16 && *ln - tmp != 3)
	{
		ft_make_error(BAD_BYTE, champ, tmp - champ->curr_line,
			(void*[4]){(void*)(*ln - tmp + 1), tmp - 1, 0, 0});
	}
	--(*ln);
}

void 	ft_parse_backslash(char **ln, t_string **res, t_champ *champ)
{
	char *pos;

	if ((pos = ft_strchr(g_backslash_literals, (**ln))))
	{
		if (!ft_string_push_back(res, g_chars[pos - g_backslash_literals]))
			exit(ft_free_champ(&champ, 666));
	}
	if (ft_isdigit(**ln) || **ln == 'x' || **ln == 'X')
	{
		ft_parse_byte(ln, res, champ);
	}

}

int 	ft_check_empty_string(char *ln, t_champ *champ, t_token_type type)
{
	while (*++ln)
	{
		if (*ln == COMMENT_CHAR)
			break ;
		if (!ft_isspace(*ln))
		{
			ft_printf(g_wrn_ignored, type == NAME ? "name" : "comment");
			ft_printf(g_pos, champ->file, champ->line,
					ln - champ->curr_line + 1);
			break ;
		}
	}
	return (1);
}

int 	ft_get_data_from_line(char *ln, t_string **res, t_token_type type, t_champ *chmp)
{
	const		size_t max_len = (size_t)--ln * 0 + (type == NAME ?
										PROG_NAME_LENGTH : COMMENT_LENGTH);
	static int	name_warning = 0;
	static int	comment_warning = 0;

	while (*++ln)
	{
		if (*ln != '"' && (!res || (*res)->len <= max_len))
		{
			if (*ln != '\\')
			{
				if (!ft_string_push_back(res, *ln))
					exit(ft_free_champ(&chmp, 666)); // todo save line begin (in champ?) for free
			}
			else if (++ln)
				ft_parse_backslash(&ln, res, chmp);
		}
		else if (*ln != '"' && (*res)->len > max_len &&
				 (type == NAME ? name_warning++ : comment_warning++) == 0 &&
				 ft_printf(g_wrn_too_long, type == NAME ? "name" : "comment"))
			ft_printf(g_pos, chmp->file, chmp->line, ln - chmp->curr_line);
		if (*ln == '"' && *(ln - 1) != '\\')
			return (ft_check_empty_string(ln, chmp, type));
	}
	return (0);
}

void		ft_parse_string(char *ln, t_string **res, t_token_type type, t_champ *champ)
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

void 	ft_parse_name_comment(t_champ *champ, char *ln, t_token_type type)
{
	int ignore;

	ignore = 0;
	if ((type == NAME ? champ->name->offset : champ->comment->offset) == 1)
	{
		ft_printf(g_wrn_double, type == NAME ? "name" : "comment");
		ft_printf(g_pos, champ->file, champ->line, 0);
		ignore = 1;
	}
	if (type == NAME)
		champ->name->offset = 1;
	else
		champ->comment->offset = 1;

	ft_validate_string(champ, &ln, type);
	if (!ignore)
		ft_parse_string(ln, type == NAME ? &champ->name : &champ->comment,
				type, champ);
	else
		ft_parse_string(ln, 0, type, champ);

}

int 	ft_parse_name(t_champ *champ, int fd)
{
	char *ln;

	while ((ln = (void*)1lu) && ft_get_next_line(fd, &ln, BUFF_SIZE) && ++champ->line)
	{
		if (!ln)
			exit(ft_free_champ(&champ, 13));
		ft_champ_upd_line(champ, ln);
		if (!ft_strncmp(ln, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
			ft_parse_name_comment(champ, ln, COMMENT);
		else if (!ft_strncmp(ln, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			ft_parse_name_comment(champ, ln, NAME);
		else if (ln[0])
			return (1);
	}
	return (1);
}

t_champ 	*ft_parser(char *file)
{
	t_champ *champ;
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1) // todo check extension
		return (0);
	if (!(champ = ft_make_champ(file, fd)))
		return (0);
	ft_parse_name(champ, fd);

	for (size_t e = 0; e < champ->errors->len; e++)
	{
		ft_printf("%s", champ->errors->data[e]);
	}
	ft_printf("<%#r>\n", champ->name->data);
	ft_printf("<%#r>\n", champ->comment->data);
//	ft_printf("<%#r>\n", "\\\\ \n");

	return (champ);
}

