#pragma once
#include "../Scene.h"

#include "game/simulation.h"
#include "game/EconPanels.h"
simulation sim;

int choosenSubMenu;

class panel
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
			 string str = "Population: ";
			 str = str + std::to_string(int(sim.population));
			 RenderText(fontShader, str, 120, 200, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
		};
};



void resetActive(int callerId);
class rootMenu
{
public:
	bool active;
	int resx; int resy;
	double x, y;

	rootMenu()
	{
		active = false;
		resx = 1280;
		resy = 1024;
	}
	virtual void draw(int resx, int resy) {};
	virtual void mouseCallback(int mx, int my) {};
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
		}
		void draw()
		{
			glUseProgram(shaderProgram);
			glm::mat4 trans;
			trans = glm::translate(trans, glm::vec3(120, 800, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform") , 1, GL_FALSE, glm::value_ptr(trans));

			drawRectangle(-100, -50, 100, 50);
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

		drawRectangle(-100, -50, 100, 50);
		RenderText(fontShader, "Report", 300, 790, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		if (choosenSubMenu == 0)
		p.draw();
	}
};








class demographicsMenu : virtual public rootMenu
{
public:
	panel p;
	demographicsMenu(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void mouseCallback(int mx, int my) {
		int size = 100;
		my = resy - my;
		if (mx > (x) && mx < (x + 2 * size) && my >(y - 0.5 * size) && my < (y + 1.5 * size))
		{
			active = !active;
			resetActive(0);
		}
			
	}
	
	void draw(int resx, int resy)
	{
		double size = 100;
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(size + x, resy - size / 2 + y, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		base.draw();
		RenderText(fontShader, "Demographics", x + size - size * 0.9, resy - size / 2 - y, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
		if (active)
			p.draw();


	}

};

class economicsMenu : virtual public rootMenu
{
public:
	econPrimaryMenu p;
	econReportMenu ep;
	economicsMenu(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void mouseCallback(int mx, int my) {
		ep.mouseInvoke(mx, my);
		p.mouseInvoke(mx, my);
		int size = 100;
		my = resy - my;
		if (mx > (x) && mx < (x + 2 * size) && my >(y - 0.5 * size) && my < (y + 1.5 * size))
		{
			active = !active;
			resetActive(1);
		}

	}
	
	void draw(int resx, int resy)
	{
		double size = 100;
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(size + x, resy - size / 2 - y, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		if (active)
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.2, 0.2, 0.2, 1);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		base.draw();
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);

		RenderText(fontShader, "Economics", x + size - size * 0.9, resy - size / 2 - y, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
		
		
		if (active)
		{
			p.draw();
			ep.draw();
		}

	}

};

class textElement
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
			string str = "Date: ";
			str = str + std::to_string(sim.date);
			RenderText(fontShader, str, 1000, 1000, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
		}
};

demographicsMenu demographics(0, 0);
economicsMenu economics(220, 0);



class mainStat : virtual public scene
{
	public:
		int resolutionX, resolutionY;
	mainStat(int resx, int resy)
	{
		resolutionX = resx;
		resolutionY = resy;
		rootMenus.push_back(&demographics);
		rootMenus.push_back(&economics);
	}
	std::vector<rootMenu*> rootMenus;
	textElement date;
	void mouseInvoke(double mx, double my)
	{
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->mouseCallback(mx, my);
		for (int i = 0; i < bn.size(); i++)
			bn[i]->mouseCallback(mx, my);
		
	}
	
	void draw()
	{
		sim.cycle();
		for (int i = 0; i < bn.size(); i++)
			bn[i]->draw();
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->draw(1280, 1024);
		date.draw();
	}
	private:

};



mainStat mainScene(1280, 1024);

void resetActive(int callerId)
{
	for (int i = 0; i < mainScene.rootMenus.size(); i++)
	{
		if (i != callerId)
			mainScene.rootMenus[i]->active = false;
	}
}