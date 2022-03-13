#pragma once
#include "../Scene.h"

#include "game/simulation.h"
#include "game/EconPanels.h"
#include "game/goodsExchangeTab.h"
#include "game/technologyTab.h"
#include "geographyTab.h"
simulation sim;

int choosenSubMenu;
int choosenTab;
class panel
{
	public:
		ageChart pyrChart;

		void draw()
		{
			double temp;
			double stage;
			for (int i = 0; i < 1600; i++)
			{
				temp = 0;
				for (int c = 0; c < 24; c++)
					temp += sim.population.agePyramid[i*25+c];
				pyrChart.data[i] = temp;
			}
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

			 string str = "Food supply: ";
			 str = str + std::to_string(int(sim.population.foodSupply));
			 RenderText(fontShader, str, 120, 170, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			 str = "Population: ";
			 str = str + std::to_string(int(sim.population.population));
			 RenderText(fontShader, str, 120, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			 str = "Dependancy rate: ";
			 str = str + std::to_string((sim.population.dependencyRate));
			 RenderText(fontShader, str, 120, 300, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			 str = "Deaths: ";
			 str = str + std::to_string((int(sim.population.fat)));
			 RenderText(fontShader, str, 120, 350, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			 str = "Births: ";
			 str = str + std::to_string(int((sim.population.births)));
			 RenderText(fontShader, str, 120, 400, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			 pyrChart.draw();
		};
};



void resetActive();
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
	virtual void draw() {};
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
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform") , 1, GL_FALSE, glm::value_ptr(trans));
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
		my = screenResolution.y - my;
		if (mx > (x) && mx < (x + 2 * size) && my >(y - 0.5 * size) && my < (y + 1.5 * size))
		{
			bool actTemp = active;
			resetActive();
			if (actTemp == false)
				active = true;
		}
			
	}
	
	void draw()
	{
		double size = 100;
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(size + x, screenResolution.y - 50 - size / 2 + y, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		base.draw();
		RenderText(fontShader, "Demographics", x + size - size * 0.9, screenResolution.y - 50 - size / 2 - y, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
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
		my = screenResolution.y - my;
		if (mx > (x) && mx < (x + 2 * size) && my >(y - 0.5 * size) && my < (y + 1.5 * size))
		{
			bool actTemp = active;
			resetActive();
			if (actTemp == false)
				active = true;
		}

	}
	
	void draw()
	{
		double size = 100;
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(size + x, screenResolution.y - 50 - size / 2 - y, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		if (active)
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.2, 0.2, 0.2, 1);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		base.draw();
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);

		RenderText(fontShader, "Economics", x + size - size * 0.9, screenResolution.y - 50 - size / 2 - y, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
		
		
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
goodsTab gt;
technologyTab tt;
geographyTab geoTab;
class mainStat : virtual public scene
{
	public:
		int resolutionX, resolutionY;
	mainStat()
	{

		rootMenus.push_back(&demographics);
		rootMenus.push_back(&economics);
		gt.reset = resetActive;
		tt.reset = resetActive;
		geoTab.reset = resetActive;
	}
	std::vector<rootMenu*> rootMenus;
	textElement date;
	void mouseInvoke(double mx, double my)
	{
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->mouseCallback(mx, my);
		for (int i = 0; i < bn.size(); i++)
			bn[i]->mouseCallback(mx, my);
		gt.mouseInvoke(mx, my);
		tt.mouseInvoke(mx, my);
		geoTab.mouseInvoke(mx, my);

	}
	
	void draw()
	{

		for (int i=0;i<5;i++)
		sim.cycle();


		for (int i = 0; i < bn.size(); i++)
			bn[i]->draw();
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->draw();

		gt.draw();
		tt.draw();
		date.draw();
		geoTab.draw();
	}
	private:

};



mainStat mainScene;

void resetActive()
{
	for (int i = 0; i < mainScene.rootMenus.size(); i++)
	{
			mainScene.rootMenus[i]->active = false;
	}
	gt.active = false;
	tt.active = false;
	geoTab.active = false;
}