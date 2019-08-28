/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_project_assets.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 05:54:59 by axtazy            #+#    #+#             */
/*   Updated: 2019/07/04 17:09:22 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_PROJECT_ASSETS_H
# define LIBFT_FT_PROJECT_ASSETS_H

/*
**		Project status flags
*/
# define PA_DPROJ			1u
# define PA_DFUNC			2u

/*
**		Error definitions
*/
# define ARG2MANY			"Too many arguments"
# define ARGINV				"Invalide arguments"
# define ARGBA(x)			"Bad argument: '"x"'"
# define ERRALLOC			"Memory allocated error"
# define ERROPEN			"File does not open"
# define ERRDIR(x)			"'"x"' is a directory"
# define ERRNULLP			"Dereferencing NULL pointer error"

void	ft_error(char const *error_line,
						char const *function_name);

#endif
