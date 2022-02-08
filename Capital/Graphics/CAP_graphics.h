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
class graphicTiles : public graphicObject
{
public:
//	void draw();
//	void init();
};
struct circleBase
{
	GLuint VAO, VBO;
	void circleInit()
	{
		VAO = 0;
		GLfloat vertices[1080];
		int acc = 0;
		for (int i = 0; i < 359; i++)
		{
			vertices[i * 3] = sin(i * PI / 180) * 50;
			vertices[i * 3 + 1] = cos(i * PI / 180) * 50;
			vertices[i * 3 + 2] = 0;
			//std::cout << vertices[i * 3];
		}
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void drawCircle(int x, int y, int radius)
	{

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
		glBindVertexArray(0);
	}
};

extern graphicObject base;
extern circleBase circle;
extern graphicTiles baseGT;
extern GLuint shaderProgram;
extern GLuint fontShader;