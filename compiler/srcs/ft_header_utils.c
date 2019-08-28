/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 09:09:07 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/26 09:09:07 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_parse_byte(char **ln, t_string **res, t_champ *champ)
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
		ft_make_error(BAD_BYTE, champ, tmp - champ->curr_ln,
				(void*[4]){(void*)(*ln - tmp + 1), tmp - 1, 0, 0});
	}
	--(*ln);
}

void	ft_parse_backslash(char **ln, t_string **res, t_champ *champ)
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

int		ft_check_empty_string(char *ln, t_champ *champ, t_token_type type)
{
	while (*++ln)
	{
		if (*ln == COMMENT_CHAR || *ln == ALT_CMT_CHAR)
			break ;
		if (!ft_isspace(*ln))
		{
			ft_printf(g_is_silent ? "" : g_wrn_ignored,
					type == NAME ? "name" : "comment");
			ft_printf(g_is_silent ? "" : g_pos,
					champ->file, champ->line,
					ln - champ->curr_ln + 1);
			break ;
		}
	}
	return (1);
}

void	ft_skip_line(char *ln, int *qoute_count)
{
	int was_slash;

	was_slash = 0;
	while (*ln)
	{
		*qoute_count -= !was_slash && *ln == '"';
		was_slash = *ln == '\\';
		++ln;
	}
}

void	ft_skip_string(t_champ *champ, char *ln)
{
	int	qoute_count;

	qoute_count = 2;
	ft_skip_line(ln, &qoute_count);
	while (qoute_count > 0 && (ln = (void*)1lu) &&
		ft_get_next_line(champ->fd, &ln, BUFF_SIZE) && ++champ->line)
	{
		if (!ln)
			exit(ft_free_champ(&champ, 13));
		ft_champ_upd_line(champ, ln);
		ft_skip_line(ln, &qoute_count);
	}
}
