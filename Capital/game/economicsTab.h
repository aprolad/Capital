#pragma once
#include "../Interface/tab.h"
#include "../Header.h"
#include "simulation.h"
#include "../Graphics/chartBuilder.h"
extern simulation sim;
extern int choosenSubMenu;

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
	virtual void draw() {};
	void drawBase()
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
	}
};

class agricultureSubPanel : public econSubPanel
{
public:
	agricultureSubPanel()
	{
		y = 200;
		id = 0;
	}
	void draw()
	{

		if (active)
		{
			drawBase();

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
			drawBase();

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
class forestrySubPanel : public econSubPanel
{
public:
	forestrySubPanel()
	{
		y = 300;
		id = 2;
	}
	void draw()
	{
		if (active)
		{
			drawBase();

			str = "Mining workers: ";
			str = str + std::to_string(int(sim.mining.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			str = "Total arable land: ";
			str = str + std::to_string(int(sim.geo.totalArableLand));
			RenderText(fontShader, str, 620, 250, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}

		str = "Forestry GDP: ";
		str = str + std::to_string(sim.GDP.miningGDP);
		RenderText(fontShader, str, 120, y - 10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class fishingSubPanel : public econSubPanel
{
public:
	fishingSubPanel()
	{
		y = 350;
		id = 3;
	}
	void draw()
	{
		if (active)
		{
			drawBase();

			str = "Mining workers: ";
			str = str + std::to_string(int(sim.mining.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			str = "Total arable land: ";
			str = str + std::to_string(int(sim.geo.totalArableLand));
			RenderText(fontShader, str, 620, 250, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}

		str = "Fishing GDP: ";
		str = str + std::to_string(sim.GDP.miningGDP);
		RenderText(fontShader, str, 120, y - 10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class huntingSubPanel : public econSubPanel
{
public:
	huntingSubPanel()
	{
		y = 400;
		id = 4;
	}
	void draw()
	{
		if (active)
		{
			drawBase();

			str = "Mining workers: ";
			str = str + std::to_string(int(sim.mining.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			str = "Total arable land: ";
			str = str + std::to_string(int(sim.geo.totalArableLand));
			RenderText(fontShader, str, 620, 250, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}

		str = "Hunting GDP: ";
		str = str + std::to_string(sim.hunting.output);
		RenderText(fontShader, str, 120, y - 10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};

class econPanel
{
public:
	virtual void mouseInvoke(int mx, int my) {};
	virtual void draw() {};
};

class EconPanelPrimary : virtual public econPanel
{
public:
	EconPanelPrimary()
	{
		agSub.choosen = &choosen;
		mgSub.choosen = &choosen;
		frSub.choosen = &choosen;
		fhSub.choosen = &choosen;
		huSub.choosen = &choosen;

		subPanels.push_back(&agSub);
		subPanels.push_back(&mgSub);
		subPanels.push_back(&frSub);
		subPanels.push_back(&fhSub);
		subPanels.push_back(&huSub);
	}
	int active;
	int choosen;
	std::vector<econSubPanel*> subPanels;
	agricultureSubPanel agSub;
	miningSubPanel mgSub;
	forestrySubPanel frSub;
	fishingSubPanel fhSub;
	huntingSubPanel huSub;
	void mouseInvoke(int mx, int my)
	{
		for (int i = 0; i < subPanels.size(); i++)
			subPanels[i]->mouseInvoke(mx, my);
	}

	void draw()
	{
		
		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(300, 350, 0.0f));
		trans = glm::scale(trans, glm::vec3(2, 2, 2));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-100, -150, 100, 150);
		

		string str = "Labor pool: ";
		str = str + std::to_string(int(sim.population.laborPool));
		RenderText(fontShader, str, 120, 600, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		
		for (int i = 0; i < subPanels.size(); i++)
		{
			subPanels[i]->draw();
			if (choosen != subPanels[i]->id)
				subPanels[i]->active = false;
		}
	};
};

class EconPanelReport : virtual public econPanel
{
public:
	EconPanelReport()
	{
		ch = new chart(900);
	}
	chart* ch;
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

class EconPanelSecondary : virtual public econPanel
{
public:
	EconPanelSecondary()
	{
		agSub.choosen = &choosen;
		mgSub.choosen = &choosen;
		frSub.choosen = &choosen;
		fhSub.choosen = &choosen;
		huSub.choosen = &choosen;

		subPanels.push_back(&agSub);
		subPanels.push_back(&mgSub);
		subPanels.push_back(&frSub);
		subPanels.push_back(&fhSub);
		subPanels.push_back(&huSub);
	}
	int active;
	int choosen;
	std::vector<econSubPanel*> subPanels;
	agricultureSubPanel agSub;
	miningSubPanel mgSub;
	forestrySubPanel frSub;
	fishingSubPanel fhSub;
	huntingSubPanel huSub;
	void mouseInvoke(int mx, int my)
	{
		for (int i = 0; i < subPanels.size(); i++)
			subPanels[i]->mouseInvoke(mx, my);
	}

	void draw()
	{

		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(300, 350, 0.0f));
		trans = glm::scale(trans, glm::vec3(2, 2, 2));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-100, -150, 100, 150);


		string str = "Labor pool: ";
		str = str + std::to_string(int(sim.population.laborPool));
		RenderText(fontShader, str, 120, 600, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		for (int i = 0; i < subPanels.size(); i++)
		{
			subPanels[i]->draw();
			if (choosen != subPanels[i]->id)
				subPanels[i]->active = false;
		}
	};
};
class econMenu
{
public:
	double x, y;
	int id;
	econPanel* p;
	virtual void draw() {};
	void drawBase()
	{
		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		if (choosenSubMenu == id)
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.2, 0.2, 0.2, 1);

		drawRectangle(-100, -50, 100, 50);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);

		if (choosenSubMenu == id)
			p->draw();
	}
	void mouseInvoke(int mx, int my)
	{
		if (mx > x - 100 && mx < x + 100 && my > y - 50 && my < y + 50)
		{
			choosenSubMenu = id;
		}
		if (choosenSubMenu == id)
		{
			p->mouseInvoke(mx, my);
		}
	}
};
class econPrimaryMenu : public econMenu
{
public:
	econPrimaryMenu()
	{
		x = 120;
		y = 800;
		id = 0;
		p = new EconPanelPrimary();
	}

	void draw()
	{
		drawBase();

		RenderText(fontShader, "Primary sector", 50, 790, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};


class econReportMenu : public econMenu
{
public:
	econReportMenu()
	{
		x = 370;
		y = 800;
		id = 1;
		p = new EconPanelReport();
	}

	
	void draw()
	{
		
		drawBase();

		RenderText(fontShader, "Report", 300, 790, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		
	}
};

class econSecondaryMenu : public econMenu
{
public:
	econSecondaryMenu()
	{
		x = 510;
		y = 800;
		id = 2;
		p = new EconPanelSecondary();
	}

	void draw()
	{

		drawBase();
		RenderText(fontShader, "Report", 300, 790, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

	}
};





class economicsMenu : virtual public tab
{
public:
	std::vector<econMenu*> menus;
	economicsMenu(int x, int y)
	{
		this->x = 320;
		this->y = 980;

		menus.push_back(new econPrimaryMenu());
		menus.push_back(new econReportMenu());
	}
	void mouseInvoke(int mx, int my)
	{
		for (int i = 0; i < menus.size(); i++)
			menus[i]->mouseInvoke(mx, my);

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
			for (int i = 0; i < menus.size(); i++)
				menus[i]->draw();
		}

	}

};