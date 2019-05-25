
#ifndef COREWAR_VIRTUAL_MACHINE_TYPES_H
#define COREWAR_VIRTUAL_MACHINE_TYPES_H

enum			m_player_pos {FIRST, SECOND, THIRD, FOURTH};

typedef struct	s_node
{
	char*			addr;
	int32_t			sleep;

	bool			carry;
	bool			live_in_session;

	int 			player;
	struct s_node	*next;
}				t_node;

typedef struct	s_player
{
	char 			name[PROG_NAME_LENGTH + 1];
	char 			comment[COMMENT_LENGTH + 1];

	int 			ordinal_number;
	int 			start_pos;
	// ...

}				t_player;

typedef struct	s_cor_file
{
	char*			file_name;
	int 			champ_index;
}				t_cor_file;

typedef struct	s_area
{
	int32_t			round;
	int32_t			cycle_step;
	int32_t			cycle_to_die;

	char*			map;

	int 			n_players;
	t_player*		players;
	t_node*			registers;

	int				flags;
}				t_area;

#endif // COREWAR_VIRTUAL_MACHINE_TYPES_H
