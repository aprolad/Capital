#pragma once

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
GLuint createVertexShader(const char* path)
{
	std::ifstream input(path);
	std::stringstream sstr;
	std::string s;
	while (input >> sstr.rdbuf());
	s = sstr.str();
	std::cout << sstr.str() << std::endl;


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
	return vertexShader;
}
GLuint createFragmentShader(const char* path)
{


	std::ifstream input("Graphics/shaders/fragment.sh");
	std::stringstream sstr1;
	std::string s1;
	while (input >> sstr1.rdbuf());
	s1 = sstr1.str();
	const char* fr = s1.c_str();
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fr, NULL);
	glCompileShader(fragmentShader);
	GLint success1;
	GLchar infoLog1[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success1);
	if (!success1)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog1);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog1 << std::endl;
	}
	return fragmentShader;
}