
#ifndef VISUALIZATION_VISUALIZATION_H
# define VISUALIZATION_VISUALIZATION_H

# include <stdio.h>
# include <stdlib.h>
//# include <stdbool.h>
//# include <math.h>

# include "GL/glew.h"
# include "GLFW/glfw3.h"
//# include "SOIL/SOIL.h"
//# include <GL/glu.h>
//# include "GL/freeglut.h"

# define MAIN_DIR		"/home/axtazy/Projects/21-school/C_projects/corewar/\
virtual_machine/visualization/"

typedef struct s_visual t_visual;

struct s_visual
{
    GLFWwindow *window;
};

void		myApplication(t_visual *main);

#endif //VISUALIZATION_VISUALIZATION_H
