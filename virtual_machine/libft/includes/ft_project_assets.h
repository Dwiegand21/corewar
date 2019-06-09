/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_project_assets.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 05:54:59 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/09 08:47:56 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_PROJECT_ASSETS_H
#define LIBFT_FT_PROJECT_ASSETS_H

extern char		g_project_name[25];
extern int		g_project_name_def;

/*
**		Error definitions
*/
# define ARG2MANY			"Too many arguments"
# define ARGINV				"Invalide arguments"
# define ARGBA(x)			"Bad argument: "x
# define ERRALLOC			"Memory allocated error"
# define ERROPEN			"File does not open"
# define ERRDIR(x)			"'"x"' is a directory"
//# define
//# define
//# define
//# define


int			ft_project_name_init(char const *project_name);
void 		ft_error(char const * restrict error_line,
						char const * restrict function_name);

#endif //LIBFT_FT_PROJECT_ASSETS_H
