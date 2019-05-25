/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    initialisation.c                                   :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: dwiegand <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 08:56:22 by dwiegand          #+# #+#               */
/*    Updated: 2019/05/24 08:56:22 by dwiegand         ### ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int 			check_cor_file(t_cor_file *p)
{
	int32_t 	fd;
	int32_t 	magic;

	if ((fd = open(p->file_name, O_RDWR)) == -1)
		ft_error(ERR_OPEN);
	if (read(fd, NULL, 0) == -1)
		ft_error(ERR_READ);
	read(fd, &magic, 4);
	bytes_reverse(&magic, sizeof(magic));
	if (magic != COREWAR_EXEC_MAGIC)
		ft_error(INV_FILE);

	return (fd);
}

void			skip_2octets(int32_t fd)
{
	int32_t		a;
	read(fd, &a, 4);
}

int32_t 		read_cor_file(t_player *player, t_cor_file *p)
{
	int32_t 	fd;
	int32_t		code_size;

	fd = check_cor_file(p);
	if (read(fd, player->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		ft_error(INV_FILE);
	player->name[PROG_NAME_LENGTH] = 0;
	skip_2octets(fd);
	read(fd, &code_size, 4);
	bytes_reverse(&code_size, sizeof(code_size));
	if (code_size > CHAMP_MAX_SIZE)
		printf("error champ code size!\n");
	if (read(fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		ft_error(INV_FILE);
	skip_2octets(fd);

#ifdef DEBUG_
	printf("Name: %s\nComment: %s\nExec size: %d\nStart position: %d\n",
				player->name, player->comment, code_size, player->start_pos);
#endif

	return (0);
}

int 			initialization_players(t_area *p, t_cor_file *files)
{
	int32_t 	i;

	if (!(p->players = malloc(sizeof(t_player) * p->n_players)))
		ft_error(ERR_ALLOC);
	i = 0;
	while (i < p->n_players)
	{
		p->players[i].ordinal_number = files[i].champ_index;
		p->players[i].start_pos = i * MEM_SIZE / p->n_players;
		read_cor_file(p->players + i, files + i);
		i++;
	}
}

int32_t			check_flags(int32_t *av, char ***ac)
{
	int32_t 	flags;

	flags = 0;
	while (*av)
	{
		if (strcmp(*(*ac), "-dump") == 0)
			flags |= DUMP;
		else if (strcmp(*(*ac), "-v") == 0)
			flags |= VISUALIZATION;
		else
			break ;
		(*av)--;
		(*ac)++;
	}
	return (flags);
}

int32_t 		read_arguments(t_area *p, int32_t av, char **ac)
{
	int32_t 	i;
	int32_t		standart_ord_n;
	int32_t 	ordinal_number;
	t_cor_file	files[4];

	standart_ord_n = 1;
	p->flags = check_flags(&av, &ac);
	i = 0;
	while (i < av)
	{
		ordinal_number = standart_ord_n;
		if (strcmp(ac[i], "-n") == 0)
		{
			ordinal_number = atoi(ac[++i]);
			i++;
		}
		else
			standart_ord_n++;
		if (i < av && p->n_players < 4 && ft_strnequ_rev(ac[i], ".cor", 4) != 0)
		{
			files[p->n_players].file_name = ac[i];
			files[p->n_players].champ_index = ordinal_number;

#if defined DEBUG_
			printf("%d: %s\n",
				   files[p->n_players].champ_index, files[p->n_players].file_name);
#endif // DEBUG_
			p->n_players++;
		}
		else
			ft_error(INV_ARGS);
		i++;
	}

#if defined DEBUG_
	if (p->flags & VISUALIZATION)
		printf("visualization on\n");
	if (p->flags & DUMP)
		printf("dump on\n");
#endif // DEBUG_

	initialization_players(p, files);
}



t_area*			initialization_area(void)
{
	t_area*		new = NULL;

	if (!(new = malloc(sizeof(t_area))))
		ft_error(ERR_ALLOC);

	if (!(new->map = malloc(sizeof(char) * MEM_SIZE)))
		ft_error(ERR_ALLOC);

	new->cycle_to_die = CYCLE_TO_DIE;
	new->cycle_step = 0;
	new->round = 0;
	new->n_players = 0;

	new->registers = NULL;

	return (new);
}