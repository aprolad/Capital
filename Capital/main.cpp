#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "CAP_window.h"
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
GLFWwindow* window;
void OGL_mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window);
	}
}
int main()
{
	
	windowInit(window);

	glfwSetKeyCallback(window, key_callback);

	OGL_mainLoop();

	glfwTerminate();
	return 0;
}