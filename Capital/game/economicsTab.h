#pragma once
#include "../Interface/tab.h"
#include "../Header.h"
#include "simulation.h"
#include "../Graphics/chartBuilder.h"
extern simulation sim;
extern int choosenSubMenu;
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
	econSubPanel()
	{
	
	}
	string str;
	bool active;
	int id;
	int* choosen;
	double y;
	void mouseInvoke(int mx, int my);
};
class agricultureSubPanel : public econSubPanel
{
public:
	agricultureSubPanel()
	{
		y = 210;
		id = 0;
	}
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
		RenderText(fontShader, str, 120, y-10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class miningSubPanel : public econSubPanel
{
public:
	miningSubPanel()
	{
		y = 250;
		id = 1;
	}
	void draw()
	{
		if (active)
		{
			glUseProgram(shaderProgram);
			glm::mat4 trans = glm::translate(glm::mat4(), glm::vec3(800, 350, 0.0f));
			GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			drawRectangle(-200, -300, 200, 300);

			trans = glm::translate(glm::mat4(), glm::vec3(280, y, 0.0f));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.2, 0.2, 0.6, 1);
			drawRectangle(-160, -25, 180, 25);
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);

			str = "Mining workers: ";
			str = str + std::to_string(int(sim.mining.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			str = "Total arable land: ";
			str = str + std::to_string(int(sim.geo.totalArableLand));
			RenderText(fontShader, str, 620, 250, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}

		str = "Mining GDP: ";
		str = str + std::to_string(sim.GDP.miningGDP);
		RenderText(fontShader, str, 120, y-10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};





class EconPanelPrimary
{
public:
	EconPanelPrimary()
	{
		agSub.choosen = &choosen;
		mgSub.choosen = &choosen;
	}
	int active;
	int choosen;
	agricultureSubPanel agSub;
	miningSubPanel mgSub;
	void mouseInvoke(int mx, int my)
	{
		agSub.mouseInvoke(mx, my);
		mgSub.mouseInvoke(mx, my);
	}
	void resetActive()
	{

	}
	void draw()
	{
		using namespace std;
		double size = 100;
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(300, 350, 0.0f));
		trans = glm::scale(trans, glm::vec3(2, 2, 2));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-100, -150, 100, 150);
		


		string str1 = "Labor pool: ";
		str1 = str1 + std::to_string(int(sim.population.laborPool));
		RenderText(fontShader, str1, 120, 300, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
		
		agSub.draw();

		mgSub.draw();
		if (choosen == 1)
			agSub.active = false;
		else
			mgSub.active = false;
	};
};


class econPrimaryMenu
{
public:
	EconPanelPrimary p;
	void mouseInvoke(int mx, int my)
	{
		int size = 100;
		int x = 20;
		int x2 = 220;
		int y = 750;
		int y2 = 850;

		if (mx > x && mx < x2 && my > y && my < y2)
		{
			choosenSubMenu = 1;
		}
		if (choosenSubMenu == 1)
		{
			p.mouseInvoke(mx, my);
		}
	}
	void draw()
	{
		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(120, 800, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		if (choosenSubMenu == 1)
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.2, 0.2, 0.2, 1);

		drawRectangle(-100, -50, 100, 50);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);

		RenderText(fontShader, "Primary sector", 50, 790, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		if (choosenSubMenu == 1)
			p.draw();
	}
};


class econReportMenu
{
public:
	bool active;
	EconPanel p;
	void mouseInvoke(int mx, int my)
	{
		int size = 100;
		int x = 270;
		int x2 = 470;
		int y = 750;
		int y2 = 850;

		if (mx > x && mx < x2 && my > y && my < y2)
		{
			choosenSubMenu = 0;
		}
	}
	void draw()
	{
		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(370, 800, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		if (choosenSubMenu == 0)
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.2, 0.2, 0.2, 1);

		drawRectangle(-100, -50, 100, 50);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);


		RenderText(fontShader, "Report", 300, 790, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		if (choosenSubMenu == 0)
			p.draw();
	}
};


class economicsMenu : virtual public tab
{
public:
	econPrimaryMenu p;
	econReportMenu ep;
	economicsMenu(int x, int y)
	{
		this->x = 320;
		this->y = 980;
	}
	void mouseInvoke(int mx, int my)
	{
		ep.mouseInvoke(mx, my);
		p.mouseInvoke(mx, my);

		if (mx > x - 100 && mx < x + 100 && my > y - 100 && my < y + 100)
		{
			bool actTemp = active;
			reset();
			if (actTemp == false)
				active = true;
		}
	}
	void draw()
	{
		drawBase();

		RenderText(fontShader, "Economics", x - 60, y, 0.5, glm::vec3(1.0, 0.0f, 0.0f));


		if (active)
		{
			p.draw();
			ep.draw();
		}

	}

};