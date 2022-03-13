#pragma once
#include "../Header.h"
#include "simulation.h"
#include "../Graphics/chartBuilder.h"
extern simulation sim;

class EconPanel
{
public:
	EconPanel()
	{
		ch = new chart(900);
	}
	chart *ch;
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
		str = str + std::to_string(int(sim.GDP.total));
		RenderText(fontShader, str, 120, 200, size / 200, glm::vec3(1.0, 0.0f, 0.0f));

		ch->data = sim.GDP.history;
		ch->draw();
	};
};
class econSubPanel
{
public:
	void (*res)(int);
	bool active;
	int* choosen;
	void mouseInvoke(int mx, int my);
};
class agricultureSubPanel : public econSubPanel
{
public:
	void draw()
	{
		using namespace std;
		string str;
		if (active)
		{
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

			str = "Agriculture workers: ";
			str = str + std::to_string(int(sim.agriculture.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			str = "Total arable land: ";
			str = str + std::to_string(int(sim.geo.totalArableLand));
			RenderText(fontShader, str, 620, 250, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}

		str = "Agriculture GDP: ";
		str = str + std::to_string(sim.GDP.farmingGDP);
		RenderText(fontShader, str, 120, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class miningSubPanel : econSubPanel
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

		string str = "Mining GDP: ";
		str = str + std::to_string(sim.GDP.miningGDP);
		RenderText(fontShader, str, 120, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		str = "Agriculture workers: ";
		str = str + std::to_string(int(sim.agriculture.workers));
		RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		str = "Total arable land: ";
		str = str + std::to_string(int(sim.geo.totalArableLand));
		RenderText(fontShader, str, 620, 250, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};





class EconPanelPrimary
{
public:
	int active;
	agricultureSubPanel agSub;
	void mouseInvoke(int mx, int my)
	{
		agSub.mouseInvoke(mx, my);
	}
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
		str1 = str1 + std::to_string(int(sim.population.laborPool));
		RenderText(fontShader, str1, 120, 300, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
		
		agSub.draw();
	};
};
