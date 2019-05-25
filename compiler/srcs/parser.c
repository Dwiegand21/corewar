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

int 	ft_validate_string(t_champ *champ, const char *ln, t_token_type type)
{
	int pos;

	pos = type == NAME ? ft_strlen(NAME_CMD_STRING) :
		  ft_strlen(COMMENT_CMD_STRING);
	ln += pos;
	while (*ln && ft_isspace(*ln) && ++pos)
		++ln;
	if (ln[0] != '"' && ln[0])
	{
		ft_make_error(UNEXP_TOKEN, champ, pos + 1,
				(void*[4]){(void*)ln, (void*)(size_t)'"', 0, 0});
		return (0);
	}
	else if (!ln[0])
	{
		ft_make_error(SAME_LINE_EXP, champ, pos + 1,
				(void*[4]){(type == NAME ? (void*)"name" : (void*)"comment"), 0, 0, 0});
		return (0);
	}
	return (1);
}

//   \n / \101(octal) / \xff(hex) / \\(screen)

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
	if (!ft_string_push_back(res, (char)ft_atoi_base_m(ln, radix)))
		exit(ft_free_champ(&champ, 666));
	if (tmp[1] && tmp[2] && tmp[3])
		tmp[3] = tmp_char;
	if (radix == 16 && *ln - tmp != 3)
	{
		ft_make_error(BAD_BYTE, champ, tmp - champ->curr_line,
			(void*[4]){tmp, 0, 0, 0});
	}
}

void 	ft_parse_backslash(char **ln, t_string **res, t_champ *champ)
{
	char *pos;

	if ((pos = ft_strchr(g_backslash_literals, (**ln))))
	{
		if (!ft_string_push_back(res, g_chars[pos - g_backslash_literals]))
			exit(ft_free_champ(&champ, 666));
		++(*ln);
	}
	if (ft_isdigit(**ln) || **ln == 'x' || **ln == 'X')
	{
		ft_parse_byte(ln, res, champ);
	}

}

void 	ft_get_data_from_line(char *ln, t_string **res, t_token_type type, t_champ *champ)
{
	const size_t max_len = type == NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH;

	while (*ln)
	{
		if ((*res)->len < max_len)
		{
			if (*ln != '"' && *ln != '\\')
			{
				if (!ft_string_push_back(res, *ln))
					exit(ft_free_champ(&champ, 666)); // todo save line begin (in champ?) for free
			}
			else if (*ln == '\\')
			{

			}
		}
		else
		{

		}
		++ln;
	}
}

char 	*ft_parse_string(char *ln, t_string **res, t_token_type type)
{

	return (ln);
}

int 	ft_parse_name_comment(t_champ *champ, const char *ln, t_token_type type)
{
	int valide_res;

	valide_res = ft_validate_string(champ, ln, type);

	return (1);
}

int 	ft_parse_name(t_champ *champ, int fd)
{
	char *ln;

	while ((ln = (void*)1lu) && ft_get_next_line(fd, &ln, BUFF_SIZE) && ++champ->line)
	{
		if (!ln)
			return (0);
		if (!ft_strncmp(ln, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		{
			if (!ft_parse_name_comment(champ, ln, COMMENT))
			{
				return (0);
			}
		}
		else if (!ft_strncmp(ln, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{
			if (!ft_parse_name_comment(champ, ln, NAME))
			{
				return (0);
			}
		}
		else if (ln[0])
		{
			champ->curr_line = ln;
		}
	}
	return (1);
}

t_champ 	*ft_parser(char *file)
{
	t_champ *champ;
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1) // todo check extension
		return (0);
	if (!(champ = ft_make_champ(file)))
		return (0);
	ft_parse_name(champ, fd);

	for (size_t e = 0; e < champ->errors->len; e++)
	{
		ft_printf("%s", champ->errors->data[e]);
	}
	return (champ);
}

