/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/24 02:01:42 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t				check_cor_file(t_cor_file *file)
{
	int32_t		fd;
	int32_t		magic;

	if ((fd = open(file->file_name, O_RDWR)) == -1)
//		ft_error(ERR_OPEN, __func__);
		ERRF("Can not open file with name \'%s\'\n", file->file_name);
	if (read(fd, NULL, 0) == -1)
		ERRF("Can not read file with name \'%s\'\n", file->file_name);
	read(fd, &magic, 4);
	bytes_reverse(&magic, sizeof(magic));
	if (magic != COREWAR_EXEC_MAGIC)
		ERRF("File with name \'%s\' is invalid\nMagic key not found.\n",
				file->file_name);
	return (fd);
}

static inline void	skip_2octets(int32_t fd)
{
	int32_t		a;

	read(fd, &a, 4);
}

int32_t				set_code_to_map(t_area *area, t_cor_file *files,
		int p_index)
{
// todo the condition does not cover all possible cases
	if ((read(files[p_index].fd,
			area->map + area->players[p_index].start_pos,
			files[p_index].code_size)) != files[p_index].code_size)
		ERRF("File with name \'%s\' is invalid:\nCode size in file is wrong.",
				files[p_index].file_name);
	load_process(area, p_index, area->players[p_index].start_pos);
	close(files->fd);
	return (0);
}

int32_t				read_cor_file(t_player *player, t_cor_file *files)
{
	int32_t		code_size;

	files->fd = check_cor_file(files);
	if (read(files->fd, player->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		ERRF("File with name \'%s\' is invalid:\nFile size is too small\n",
				files->file_name);
	player->name[PROG_NAME_LENGTH] = 0;
	skip_2octets(files->fd);
	read(files->fd, &code_size, 4);
	bytes_reverse(&code_size, sizeof(code_size));
	if (code_size > CHAMP_MAX_SIZE)
		ERRF("File with name \'%s\' is invalid:\n"
			"Code size in size bytes greater than maximum code size constant\n",
			files->file_name);
	if (read(files->fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		ERRF("File with name \'%s\' is invalid:\nFile size is too small\n",
				files->file_name);
	skip_2octets(files->fd);
	files->code_size = code_size;
	return (0);
}

int32_t				initialization_players(t_area *area, t_cor_file *files)
{
	uint32_t	i;

	if (!(area->players = malloc(sizeof(t_player) * SN_PLAYERS)))
		ERRF(ERRALLOC);
	i = 0;
	while (i < SN_PLAYERS)
	{
		area->players[i].ordinal_number = files[i].champ_index;
		area->players[i].start_pos = i * MEM_SIZE / SN_PLAYERS;
		area->players[i].last_live = 0;
		read_cor_file(area->players + i, files + i);
		set_code_to_map(area, files, i);
		i++;
	}
	i = 0;
	printf("Introducing contestants...\n");
	while (i < SN_PLAYERS)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				area->players[i].ordinal_number, files[i].code_size,
				area->players[i].name, area->players[i].comment);
		i++;
	}
	fflush(stdout);
	return (0);
}
