#include "Graphics/CAP_graphics.h"
GLuint VBO1, VAO1, VBO2, VAO2;
void graphicObject::init()
{
	GLfloat vertices[] = {
	50.0f, -50.0f, 0.0f,
	50.0f, 50.0f, 0.0f,
	-50.0f, -50.0f, 0.0f,
	-50.0f, 50.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);


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


void drawRectangle(double x1, double y1, double x2, double y2)
{
	GLfloat vertices[] = {
	x1, y1, 0.0f,
	x1, y2, 0.0f,
	x2, y1, 0.0f,
	x2, y2, 0.0f
	};

	

	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO1);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void drawLine(double x1, double y1, double x2, double y2)
{
	GLfloat vertices[] = {
	x1, y1, 0.0f,
	x2, y2, 0.0f,
	};



	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO1);
	glDrawArrays(GL_LINE_LOOP, 0, 2);
	glBindVertexArray(0);
}

graphicObject base;
GLuint shaderProgram;
GLuint fontShader;