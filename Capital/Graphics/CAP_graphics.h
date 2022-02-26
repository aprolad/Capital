#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#define PI 3.14159265
class graphicObject
{
	protected:
		GLuint VBO, VAO;
	public:
	void init();
	void draw();
};

void drawRectangle(double x1, double y1, double x2, double y2);
extern graphicObject base;
extern GLuint shaderProgram;
extern GLuint fontShader;