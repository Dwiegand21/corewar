
#ifndef VISUALIZATION_VISUALIZATION_H
# define VISUALIZATION_VISUALIZATION_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>


# include "SOIL/SOIL.h"
# include <GL/gl.h>
# include <GL/glu.h>

# define IMAGE_DIR "/home/axtazy/Projects/21-school/C_projects/corewar/virtual_machine/visualization/textures/"

typedef struct s_visual t_visual;

void
GLFW_example(void);
int
SDL_example(int argc, char **argv);
void
GLUT_example(int argc, char** argv);
#endif //VISUALIZATION_VISUALIZATION_H
