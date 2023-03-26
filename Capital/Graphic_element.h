#pragma once
#include "Header.h"
class Graphic_element
{
protected:
	GLuint VBO, VAO;
	GLuint shaderProgram, fontShader;

public:
	void (*action) ();
	virtual void mouseCallback(double, double) {};
	virtual void init() {};
	virtual void draw() {};
};

class Quad_button : virtual public Graphic_element
{
public:
	int x, y, size;
	std::string text;
	Quad_button(GLuint shader, GLuint font, int ax, int ay, std::string atext)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size = 100;
		text = atext;
	}
	void mouseCallback(double mx, double my)
	{
		if (mx > (x - size) && mx < (x + size) && my >(y - size) && my < (y + size))
			action();
	}
	void init()
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
	void draw()
	{
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
		trans = glm::scale(trans, glm::vec3(100 / 50, 100 / 50, 100 / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		RenderText(fontShader, text, x - 100 * 0.85, y, 150 / 150, glm::vec3(1.0, 0.0f, 0.0f));

	}

};