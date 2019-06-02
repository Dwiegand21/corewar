/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:45:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/02 06:19:51 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		help()
{
	write(1, "help <<\n", 8);
}


int32_t		main(int argc, char **argv)
{
	t_area		*area;

	area = NULL;
	int 	a = 0xFF00AA77;
	printf("%x :: %x\n", a, be_get32(&a));
	short int b = 0xF71A;
	printf("%hx :: %hx\n", b , be_get16(&b));
	if (argc == 1)
	{
		help();
	}
	else
	{
		area = initialization_area();
		read_arguments(area, argc - 1, argv + 1);
	}
	free_args(&area);
	return 0;
}
