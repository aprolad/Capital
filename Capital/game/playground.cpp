#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "playground.h"
#include <algorithm>
bool comp(src a, src b) {
	return a.dist < b.dist;
}
void playground::draw()
{

	double ms = 50;
	glUseProgram(shaderProgram);
	double size = 10;
	glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	glLineWidth(3.0f);

	GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
	GLuint colorLoc = glGetUniformLocation(shaderProgram, "ourColor");
	GLuint colorTLoc = glGetUniformLocation(shaderProgram, "colorTarget");
	for (int y = 0; y < ms; y++)
		for (int x = 0; x < ms; x++)
		{
			int min = 10000;
			
			for (int i = 0; i < conc.size(); i++)
			{
					conc[i].distance(x, y);
			}

			sort(conc.begin(), conc.end(), comp);
			trans = glm::mat4(1);
			trans = glm::translate(trans, glm::vec3(x * size * 2 + 50, y * size * 2 + 50, 0.0f));
			trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			glUniform4f(colorLoc, 0.0f, float(soil[x][y].fert), 0.0f, 1.0f);
			glUniform4f(colorTLoc, conc[0].x * size * 2 + 50, conc[0].y * size * 2 + 50, conc[1].x * size * 2 + 50, conc[1].y * size * 2 + 50);
			//std::cout << conc[0].x << " " << conc[0].y <<std::endl;
			soil[0][0].gr.draw();
		}
	glUniform4f(colorLoc, 0.0f, 0, 0.0f, 1.0f);
}