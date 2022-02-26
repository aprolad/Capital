#pragma once
#include "../Scene.h"
#include "simulation.h"
extern simulation sim;

class EconPanel
{
public:
	void draw()
	{
		using namespace std;
		double size = 100;
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(200, 200, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-50, -50, 50, 50);
		string str = "GDP: ";
		str = str + std::to_string(sim.GDP);
		RenderText(fontShader, str, 120, 200, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
	};
};