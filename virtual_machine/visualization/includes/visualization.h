
#ifndef VISUALIZATION_VISUALIZATION_H
# define VISUALIZATION_VISUALIZATION_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include "GL/glew.h"
# include "GLFW/glfw3.h"
//# include "../external/soil-1.16/inc/SOIL/SOIL.h"
# include "SOIL/SOIL.h"

typedef struct s_visual t_visual;

struct s_visual
{
    GLFWwindow *window;
};

#endif //VISUALIZATION_VISUALIZATION_H
