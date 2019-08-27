/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:43:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/25 19:43:38 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // todo delete
#include <sys/stat.h>
#include "asm.h"

static inline int	ft_isdir(char *name)
{
	struct stat statbuf;
	if (stat(name, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

static inline char	*ft_change_postfix(char *src)
{
	char *const		ext_pos = ft_rstrchr(src, '.') ;
	char 			*ret;

	if (!ext_pos)
		return (ft_strjoin(src, ".cor"));
	*ext_pos = '\0';
	ret = ft_strjoin(src, ".cor");
	*ext_pos = '.';
	return (ret);
}

static inline char 	*ft_add_slash_if_need(char *dir)
{
	const size_t len = ft_strlen(dir);

	if (!len)
		return (ft_strjoin(dir, "\0"));
	if (dir[len - 1] == '/')
		return (ft_strjoin(dir, "\0"));
	return (ft_strjoin(dir, "/"));
}

char				*ft_get_out_name(char *src, char *out)
{
	char *name;
	char *tmp;

	if (out && ft_isdir(out))
	{
		name = ft_rstrchr(src, '/');
		name = !name ? src : name + 1;
		if (!(out = ft_add_slash_if_need(out)))
			return (0);
		tmp = out;
		if (!(out = ft_strjoin(out, name)) && free_ret(tmp, 1))
			return (0);
		free(tmp);
		tmp = out;
		if (!(out = ft_change_postfix(out)) && free_ret(out, 1))
			return (0);
		free (tmp);
		return (out);
	}
	if (out)
		return (ft_strjoin(out, "\0"));
	return (ft_change_postfix(src));
}

int ft_compile_one(char *src, char *out)
{
	t_champ	*champ;
	int		fd;

	if (!(champ = ft_parser(src)) || !ft_translate_to_bytecode(champ) || champ->error_count)
		return (ft_free_champ(&champ, 1) +
			ft_printf("Error while compiling file '%s'\n", src) * 0);
	if ((fd = open(out, O_CREAT | O_TRUNC | O_WRONLY, 0666)) == -1)
		return (ft_free_champ(&champ, 1) +
			ft_printf("Error while opening file '%s'\n", out) * 0);
	if (write(fd, champ->res->data, champ->res->len) == -1)
		return (ft_free_champ(&champ, 1) +
			ft_printf("Error while writing to file '%s'\n", out) * 0);
	ft_free_champ(&champ, 0);
	ft_printf("Compiled %s to %s\n", src, out);
	return (0);
}

int ft_compile_all(t_flags *fl)
{
	size_t	i;
	size_t	j;
	char	*out;
	int 	error_count;

	i = -1;
	j = 0;
	error_count = 0;
	while (++i < fl->srcs->len)
	{
		if ((size_t)fl->srcs->data[i] & (1lu << 63u))
		{
			fl->srcs->data[i] =
					(void*)((size_t)fl->srcs->data[i] & ~(1lu << 63u));
			out = ft_get_out_name(fl->srcs->data[i], fl->outputs->data[j++]);
		}
		else
			out = ft_get_out_name(fl->srcs->data[i], 0);
		error_count += ft_compile_one(fl->srcs->data[i], out);
		free(out);
	}
	return (1);
}

int main(int ac, char **av)
{
	t_flags		*fl;

	if (!(fl = ft_find_s_h_flags(ac, (const char *const *)av)))
		exit(1);
	ft_parse_flags(fl, ac, av);
	ft_compile_all(fl);
	ft_free_flags(fl, 0);
	return (0);
}