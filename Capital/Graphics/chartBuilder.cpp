

#include "../Header.h"
#include "chartBuilder.h"
#include <algorithm>
using namespace std;
void chart::draw()
{
	std::vector<double>::iterator min = std::min_element(std::begin(data), std::end(data));
	std::vector<double>::iterator max = std::max_element(std::begin(data), std::end(data));

	double range = (*max - *min) + 1;
	double sizing = 0;//	*max = 400;
	glUseProgram(shaderProgram);
	glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(700, 350, 0.0f));
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	int dtr = 0;
	GLfloat vertices[300];
	for (int i = 299; i > 0; i -= 3)
	{
		vertices[i - 2] = i;
		vertices[i - 1] = (data[dtr]- *min)/(*max - *min + 1) * 400;
		vertices[i ] = 0;
		dtr++;
	};

	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO1);
	glDrawArrays(GL_LINE_STRIP, 0, 100);
	glBindVertexArray(0);
}

void ageChart::draw()
{
	std::vector<double>::iterator min = std::min_element(std::begin(data), std::end(data));
	std::vector<double>::iterator max = std::max_element(std::begin(data), std::end(data));

	double range = (*max - *min) + 1;
	double sizing = 0;//	*max = 400;
	glUseProgram(shaderProgram);
	glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(700, 350, 0.0f));
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	int dtr = 0;
	GLfloat vertices[300];
	for (int i = 0; i < 300; i += 3)
	{
		vertices[i] = i;
		vertices[i + 1] = (data[dtr] - *min) / (*max - *min + 1) * 400;
		vertices[i + 2] = 0;
		dtr++;
	};

	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO1);
	glDrawArrays(GL_LINE_STRIP, 0, 100);
	glBindVertexArray(0);
}