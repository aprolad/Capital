#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#define PI 3.14159265
extern GLuint VBO1, VAO1;
extern GLuint VBO2, VAO2;
class graphicObject
{
	protected:
		GLuint VBO, VAO;
	public:
	void init();
	void draw();
};

void drawRectangle(double x1, double y1, double x2, double y2);
void drawLine(double x1, double y1, double x2, double y2);
extern graphicObject base;
extern GLuint shaderProgram;
extern GLuint fontShader;