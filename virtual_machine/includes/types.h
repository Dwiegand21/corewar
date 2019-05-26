
#ifndef COREWAR_VIRTUAL_MACHINE_TYPES_H
#define COREWAR_VIRTUAL_MACHINE_TYPES_H

enum			m_player_pos {FIRST, SECOND, THIRD, FOURTH};

typedef struct	s_process
{
	uint8_t*		addr;
	int32_t			sleep;

	int32_t 		reg[REG_NUMBER];

	bool			carry;
	bool			live_in_session;

	uint32_t 		player;
	struct s_node	*next;

}				t_process;

typedef struct	s_player
{
	char 			name[PROG_NAME_LENGTH + 1];
	char 			comment[COMMENT_LENGTH + 1];

	uint32_t 		ordinal_number;
	uint32_t 		start_pos;

	// ...

}				t_player;

typedef struct	s_cor_file
{
	char*			file_name;
	int32_t 		champ_index;

	int32_t			fd;
	int32_t 		code_size;
}				t_cor_file;

typedef struct	s_area
{
	int32_t			round;
	int32_t			cycle_step;
	int32_t			cycle_to_die;

	uint8_t*		map;

	int32_t			n_players;
	t_player*		players;
	t_process*		processes;

	uint32_t		flags;
}				t_area;

#endif // COREWAR_VIRTUAL_MACHINE_TYPES_H
