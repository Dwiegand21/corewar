/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    parser.c                                           :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: ggerardy <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 10:42:03 by ggerardy          #+# #+#               */
/*    Updated: 2019/05/24 10:42:03 by ggerardy         ### ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int 	ft_parse_champ(t_champ *champ) {

	champ = 0;
	return (1);
}

int 	ft_check_header(t_champ *champ)
{
	if (champ->name)
	{

	}
	return (1);
}

int 	ft_parse_string(t_champ *champ, const char *ln, t_token_type type)
{
	char *err;
	int pos;

	pos = type == NAME ? ft_strlen(NAME_CMD_STRING) :
						ft_strlen(COMMENT_CMD_STRING);
	ln += pos;
	while (*ln && ft_isspace(*ln) && ++pos)
		++ln;
	if (ln[0] != '"')
	{
		ft_sprintf(&err, errors[UNEXP_TOKEN], ln, champ->line, pos, '"');
		if (!err || !ft_vector_push_back(&champ->errors, err))
			exit(ft_free_champ(&champ, 666));
	}
	else if (!ln[0])
	{
		ft_sprintf(&err, errors[SAME_LINE_EXP], type == NAME ?
			"name" : "comment", champ->line, pos);
		if (!err || !ft_vector_push_back(&champ->errors, err))
			exit(ft_free_champ(&champ, 666));
	}

}

int 	ft_parse_name(t_champ *champ, int fd)
{
	char *ln;

	while ((ln = (void*)1lu) && ft_get_next_line(fd, &ln, BUFF_SIZE))
	{
		if (!ln)
			return (0);
		if (!ft_strncmp(ln, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		{
			if (!ft_parse_string(champ, ln, COMMENT))
			{
				return (0);
			}
		}
		else if (!ft_strncmp(ln, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{
			if (!ft_parse_string(champ, ln, NAME))
			{
				return (0);
			}
		}
		else if (ln[0])
		{
			champ->tmp = ln;
		}
	}
	return (1);
}

t_champ 	*ft_parser(char *file)
{
	t_champ *champ;
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	if (!(champ = ft_make_champ()))
		return (0);
	ft_parse_name(champ, fd);

	for (size_t e = 0; e < champ->errors->len; e++)
	{
		ft_printf("%s", champ->errors->data[e]);
	}

}

