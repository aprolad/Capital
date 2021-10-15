#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>

class graphicObject
{
	private:
		GLuint VBO, VAO;
	public:
	void init();
	void draw();
};
extern graphicObject base;
extern GLuint shaderProgram;
extern GLuint fontShader;