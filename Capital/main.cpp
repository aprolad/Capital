#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "CAP_window.h"
#include "Graphics/CAP_shaderAux.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* window;


void OGL_mainLoop()
{
	

	GLuint vertexShader = createVertexShader("Graphics/shaders/vertex.sh");
	GLuint fragmentShader = createFragmentShader("Graphics/shaders/fragment.sh");
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success2;
	GLchar infoLog2[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);
	if (!success2)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog2 << std::endl;
	}


	GLfloat vertices[] = {
		  -0.5f, -0.5f, 0.0f,
		   0.5f, -0.5f, 0.0f,
		   0.0f,  0.5f, 0.0f  
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);



	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		


		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

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