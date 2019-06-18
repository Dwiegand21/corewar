//
//#include "visualization.h"
//
//void		myApplication(t_visual *main)
//{
//	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//	glEnable(GL_DEPTH_TEST);
//	// Accept fragment if it closer to the camera than the former one
//	glDepthFunc(GL_LESS);
//
//	// Cull triangles which normal is not towards the camera
//	glEnable(GL_CULL_FACE);
//
//	GLuint VertexArrayID;
//	glGenVertexArrays(1, &VertexArrayID);
//	glBindVertexArray(VertexArrayID);
//
///*----------------------------------------------------------------------------*/
//
//	GLfloat texCoords[] = {
//			0.0f, 0.0f,  // Нижний левый угол
//			1.0f, 0.0f,  // Нижний правый угол
//			0.5f, 1.0f   // Верхняя центральная сторона
//	};
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//
//	int width, height;
//	unsigned char* image =
//			SOIL_load_image(
//					MAIN_DIR"textures/300px-Bump1.jpg",
//					&width,
//					&height,
//					0,
//					SOIL_LOAD_RGB);
//
//	GLuint texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	printf("image: %p\ntexture: %u\n", image, texture);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	//glGenerateMipmap(GL_TEXTURE_2D);
//	//SOIL_free_image_data(image);
//	//glBindTexture(GL_TEXTURE_2D, 0);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	//glfwSwapBuffers(main->window);
//
//	while (glfwGetKey(main->window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
//		&& glfwWindowShouldClose(main->window) == 0)
//	{
//		glfwPollEvents();
//	}
//	glfwTerminate();
//}