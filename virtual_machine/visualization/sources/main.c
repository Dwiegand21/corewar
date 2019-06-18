//
// Created by axtazy on 6/17/19.
//

#include "visualization.h"
//#include <GL/gl.h>

/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64
//static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
//
//static GLuint texName;
//
//void makeCheckImage(void)
//{
//	int i, j, c;
//
//	for (i = 0; i < checkImageHeight; i++) {
//		for (j = 0; j < checkImageWidth; j++) {
//			c = ((((i&0x8)==0)^((j&0x8))==0))*255;
//			checkImage[i][j][0] = (GLubyte) c;
//			checkImage[i][j][1] = (GLubyte) c;
//			checkImage[i][j][2] = (GLubyte) c;
//			checkImage[i][j][3] = (GLubyte) 255;
//		}
//	}
//}
//
//void init(void)
//{
//	glClearColor (0.0, 0.0, 0.0, 0.0);
//	glShadeModel(GL_FLAT);
//	glEnable(GL_DEPTH_TEST);
//
//	makeCheckImage();
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	glGenTextures(1, &texName);
//	glBindTexture(GL_TEXTURE_2D, texName);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//			GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//			GL_NEAREST);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
//			checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
//			checkImage);
//}
//
//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_TEXTURE_2D);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//	glBindTexture(GL_TEXTURE_2D, texName);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
//	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
//	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
//	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
//
//	glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
//	glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
//	glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
//	glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
//	glEnd();
//	glFlush();
//	glDisable(GL_TEXTURE_2D);
//}
//
//void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
//{
//	const GLdouble pi = 3.1415926535897932384626433832795;
//	GLdouble fW, fH;
//
//	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
//	fH = tan( fovY / 360 * pi ) * zNear;
//	fW = fH * aspect;
//
//	glFrustum( -fW, fW, -fH, fH, zNear, zFar );
//}
//
//void reshape(int w, int h)
//{
//	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	perspectiveGL(60.0, (GLdouble)w / (GLdouble) h, 1.0, 30.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslatef(0.0, 0.0, -3.6);
//}
//
//void keyboard (unsigned char key, int x, int y)
//{
//	switch (key) {
//		case 27:
//			exit(0);
//		default:
//			break;
//	}
//}

int main(int argc, char** argv)
{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(250, 250);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow(argv[0]);
//	init();
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glutKeyboardFunc(keyboard);
//	glutMainLoop();


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Открыть окно и создать в нем контекст OpenGL
	GLFWwindow* window; // (В сопроводительном исходном коде эта переменная является глобальной)
	window = glfwCreateWindow( 720, 480, "Tutorial 01", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Невозможно открыть окно GLFW. Если у вас Intel GPU, то он не поддерживает версию 3.3. Попробуйте версию уроков для OpenGL 2.1.n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

// Инициализируем GLEW
	glewExperimental=1; // Флаг необходим в Core-режиме OpenGL
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Невозможно инициализировать GLEWn");
		return -1;
	}

// Включим режим отслеживания нажатия клавиш, для проверки ниже
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// Пока что ничего не выводим. Это будет в уроке 2.

		// Сбрасываем буферы
		//glfwSwapBuffers(window);
		glfwPollEvents();

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0 );

	return 0;
}
