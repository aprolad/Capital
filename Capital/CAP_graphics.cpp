#include "Graphics/CAP_graphics.h"

void graphicObject::init()
{
	GLfloat vertices[] = {
	50.0f, -50.0f, 0.0f,
	50.0f, 50.0f, 0.0f,
	-50.0f, -50.0f, 0.0f,
	-50.0f, 50.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void graphicObject::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

graphicTiles baseGT;
graphicObject base;
circleBase circle;
GLuint shaderProgram;
GLuint fontShader;