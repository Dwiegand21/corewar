/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/05/27 16:55:36 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t			check_cor_file(t_cor_file *file)
{
	int32_t		fd;
	int32_t		magic;

	if ((fd = open(file->file_name, O_RDWR)) == -1)
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

int32_t			set_code_to_map(t_area *area, t_cor_file *files, int p_index)
{
	// new process node;

	if ( (read(files[p_index].fd,
			   area->map + area->players[p_index].start_pos,
			   files[p_index].code_size)) != files[p_index].code_size )
		ft_error(INV_CODE_SIZE);

	close(files->fd);
	return (0);
}

int32_t			read_cor_file(t_player *player, t_cor_file *files)
{
	int32_t		code_size;

	files->fd = check_cor_file(files);
	if (read(files->fd, player->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		ft_error(INV_FILE);
	player->name[PROG_NAME_LENGTH] = 0;
	skip_2octets(files->fd);
	read(files->fd, &code_size, 4);
	bytes_reverse(&code_size, sizeof(code_size));
	if (code_size > CHAMP_MAX_SIZE)
		printf("error champ code size!\n");
	if (read(files->fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		ft_error(INV_FILE);
	skip_2octets(files->fd);
	if (DEBUG_)					// DEBUG_ # # #
	{
		printf("\nName: %s\nComment: %s\nExec size: %d\nStart position: %d\n"
				"Player_number: %d\n",
				player->name,
				player->comment,
				code_size,
				player->start_pos,
				player->ordinal_number);
	}
	files->code_size = code_size;
	return (0);
}

int32_t			initialization_players(t_area *area, t_cor_file *files)
{
	int32_t		i;

	if (!(area->players = malloc(sizeof(t_player) * area->n_players)))
		ft_error(ERR_ALLOC);
	i = 0;
	while (i < area->n_players)
	{
		area->players[i].ordinal_number = files[i].champ_index;
		area->players[i].start_pos = i * MEM_SIZE / area->n_players;
		read_cor_file(area->players + i, files + i);
		set_code_to_map(area, files, i);
		i++;
	}
	return (0);
}
