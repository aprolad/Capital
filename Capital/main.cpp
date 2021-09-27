#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "CAP_window.h"
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* window;
GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};
void OGL_mainLoop()
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	std::ifstream ifs("Graphics/shaders/vertex.sh");
	std::string s;
	while (ifs)
	{
		ifs >> s;
	}
	std::cout << s;
	const char* vertex = s.c_str();
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

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