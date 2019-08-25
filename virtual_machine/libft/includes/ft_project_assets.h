/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_project_assets.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 05:54:59 by axtazy            #+#    #+#             */
/*   Updated: 2019/08/23 05:26:04 by axtazy           ###   ########.fr       */
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
# define ERRALLOC			"Memory allocated error"
# define ERROPEN			"File does not open"
# define ERRDIR(x)			"'"x"' is a directory"
# define ERRNULLP			"Dereferencing NULL pointer error"

# define ERRF(format, args...) _print_err_with_fname(__func__, format, ## args)
# define ERR(format, args...) _print_err_without_fname(format, ## args)

void		_print_err_without_fname(
									const char *format,
									...);
void		_print_err_with_fname(
									char const *function_name,
									char const *format,
									...);



#endif
