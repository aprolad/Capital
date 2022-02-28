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
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(300, 350, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-100, -150, 100, 150);
		string str = "GDP: ";
		str = str + std::to_string(sim.GDP.total);
		RenderText(fontShader, str, 120, 200, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
	};
};
class econSubPanel
{

};
class agricultureSubPanel
{
public:
	void draw()
	{
		using namespace std;

		glUseProgram(shaderProgram);
		glm::mat4 trans = glm::translate(glm::mat4(), glm::vec3(800, 350, 0.0f));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-200, -300, 200, 300);

		trans = glm::translate(glm::mat4(), glm::vec3(280, 210, 0.0f));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.2, 0.2, 0.6, 1);
		drawRectangle(-160, -25, 180, 25);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);

		string str = "Agriculture GDP: ";
		str = str + std::to_string(sim.GDP.farmingGDP);
		RenderText(fontShader, str, 120, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		str = "Agriculture workers: ";
		str = str + std::to_string(sim.agriculture.workers);
		RenderText(fontShader, str, 820, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class EconPanelPrimary
{
public:
	agricultureSubPanel agSub;
	void draw()
	{
		using namespace std;
		double size = 100;
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(300, 350, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-100, -150, 100, 150);
		

		string str1 = "Mining GDP: ";
		str1 = str1 + std::to_string(sim.GDP.miningGDP);
		RenderText(fontShader, str1, 120, 250, size / 200, glm::vec3(1.0, 0.0f, 0.0f));

		str1 = "Labor pool: ";
		str1 = str1 + std::to_string(int(sim.laborPool));
		RenderText(fontShader, str1, 120, 300, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
	
		agSub.draw();
	};
};