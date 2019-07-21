//
// Created by axtazy on 6/17/19.
//

#include "visualization.h"

int
main(int argc, char** argv)
{
	t_visualization		v;
	int32_t				status;

	if (initialization(&v) == 0)
		return (0);

	title_page(&v);
	destroy_all(&v);

	return 0;
}
