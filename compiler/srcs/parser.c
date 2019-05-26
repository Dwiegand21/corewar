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


t_champ 	*ft_parser(char *file)
{
	t_champ *champ;
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1) // todo check extension
		return (0);
	if (!(champ = ft_make_champ(file, fd)))
		return (0);
	ft_parse_header(champ, fd);

	for (size_t e = 0; e < champ->errors->len; e++)
	{
		ft_printf("%s", champ->errors->data[e]);
	}
	ft_printf("<%s>\n", champ->name->data);
	ft_printf("<%s>\n", champ->comment->data);
	ft_printf("<%s>\n", champ->curr_line);



	return (champ);
}

