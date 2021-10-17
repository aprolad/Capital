#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>

class graphicObject
{
	protected:
		GLuint VBO, VAO;
	public:
	void init();
	void draw();
};
class graphicTiles : public graphicObject
{
public:
//	void draw();
//	void init();
};
extern graphicObject base;
extern graphicTiles baseGT;
extern GLuint shaderProgram;
extern GLuint fontShader;