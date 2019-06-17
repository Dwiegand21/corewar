//
// Created by axtazy on 6/17/19.
//

#include "visualization.h"

t_visual*
gl_initf()
{
    t_visual* main;

    if ((main = malloc(sizeof(t_visual))) == NULL || (glfwInit()) == 0)
    {
        fprintf(stderr, "Failed to initialized GLFW\n");
        exit (1);
    }
    atexit(glfwTerminate);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    main->window = glfwCreateWindow( 720, 480, "OpenGL test", NULL, NULL);
    if( main->window == NULL )
    {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        exit(1);
    }
    glfwMakeContextCurrent(main->window);
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf( stderr, "Failed to initialize GLEW\n");
        exit (1);
    }
	glfwSetInputMode(main->window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(main->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(main->window, 1024/2, 768/2);
    return (main);
}

int main()
{
    t_visual    *main;

    main = gl_initf();
    return (0);
}
