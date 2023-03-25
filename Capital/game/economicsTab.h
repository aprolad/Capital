#pragma once
#include "../Interface/tab.h"
#include "../Header.h"

#include "../Graphics/chartBuilder.h"

extern int choosenSubMenu;

class econSubPanel
{
public:
	econSubPanel(int* a)
	{
		choosen = a;
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
	agricultureSubPanel(int* choosen) : econSubPanel(choosen)
	{
		y = 200;
		id = 0;
	}
	void draw()
	{

		if (active)
		{
			drawBase();

			str = "Kg of wheat: ";
		//	str = str + std::to_string(int(sim.agriculture.wheat.naturalOutput));
			RenderText(fontShader, str, 620, 300, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			str = "Agriculture workers: ";
		//	str = str + std::to_string(int(sim.agriculture.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			str = "Total arable land: ";
		//	str = str + std::to_string(int(sim.geo.totalArableLand));
			RenderText(fontShader, str, 620, 250, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}

		str = "Agriculture GDP: ";
	//	str = str + std::to_string(int(sim.agriculture.gdp));
		RenderText(fontShader, str, 120, y-10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class miningSubPanel : public econSubPanel
{
public:
	miningSubPanel(int* choosen) : econSubPanel(choosen)
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
		//	str = str + std::to_string(int(sim.mining.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		}

		str = "Mining GDP: ";
	//	str = str + std::to_string(int(sim.mining.gdp));
		RenderText(fontShader, str, 120, y-10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class forestrySubPanel : public econSubPanel
{
public:
	forestrySubPanel(int* choosen) : econSubPanel(choosen)
	{
		y = 300;
		id = 2;
	}
	void draw()
	{
		if (active)
		{
			drawBase();

			str = "Forestry industry workers: ";
		//	str = str + std::to_string(int(sim.mining.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			
		}

		str = "Forestry GDP: ";
		//str = str + std::to_string(int(sim.forestry.gdp));
		RenderText(fontShader, str, 120, y - 10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class fishingSubPanel : public econSubPanel
{
public:
	fishingSubPanel(int* choosen) : econSubPanel(choosen)
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
		//	str = str + std::to_string(int(sim.mining.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		}

		str = "Fishing GDP: ";
		//str = str + std::to_string(int(sim.fishing.gdp));
		RenderText(fontShader, str, 120, y - 10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};
class huntingSubPanel : public econSubPanel
{
public:
	huntingSubPanel(int* choosen) : econSubPanel(choosen)
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
			//str = str + std::to_string(int(sim.mining.workers));
			RenderText(fontShader, str, 620, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

			str = "Total arable land: ";
		//	str = str + std::to_string(int(sim.geo.totalArableLand));
			RenderText(fontShader, str, 620, 250, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}

		str = "Hunting GDP: ";
	//	str = str + std::to_string(sim.hunting.output);
		RenderText(fontShader, str, 120, y - 10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
};

class econPanel
{
public:
	int active;
	int choosen;
	virtual void mouseInvoke(int mx, int my) {};
	virtual void draw() {};
};

class EconPanelPrimary : virtual public econPanel
{
public:
	EconPanelPrimary()
	{
		subPanels.push_back(new agricultureSubPanel(&choosen));
		subPanels.push_back(new miningSubPanel(&choosen));
		subPanels.push_back(new forestrySubPanel(&choosen));
		subPanels.push_back(new fishingSubPanel(&choosen));
		subPanels.push_back(new huntingSubPanel(&choosen));
	}

	std::vector<econSubPanel*> subPanels;
	
	void mouseInvoke(int mx, int my)
	{
		for (int i = 0; i < subPanels.size(); i++)
			subPanels[i]->mouseInvoke(mx, my);
	}
	void draw()
	{
		glUseProgram(shaderProgram);
		glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(300, 350, 0.0f));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-200, -300, 200, 300);

		string str = "Labor pool: ";// + std::to_string(int(sim.population.laborPool));
		RenderText(fontShader, str, 120, 600, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		
		for (int i = 0; i < subPanels.size(); i++)
		{
			subPanels[i]->draw();
			if (choosen != subPanels[i]->id)
				subPanels[i]->active = false;
		}
	};
};

class EconPanelSecondary : virtual public econPanel
{
public:
	EconPanelSecondary() {}
	std::vector<econSubPanel*> subPanels;

	void mouseInvoke(int mx, int my)
	{
		for (int i = 0; i < subPanels.size(); i++)
			subPanels[i]->mouseInvoke(mx, my);
	}
	void draw()
	{
		glUseProgram(shaderProgram);
		glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(300, 350, 0.0f));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-200, -300, 200, 300);

		string str = "Labor pool: ";// +std::to_string(int(sim.population.laborPool));
		RenderText(fontShader, str, 120, 600, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		for (int i = 0; i < subPanels.size(); i++)
		{
			subPanels[i]->draw();
			if (choosen != subPanels[i]->id)
				subPanels[i]->active = false;
		}
	};
};
class EconPanelTetriary : virtual public econPanel
{
public:
	EconPanelTetriary() {}
	std::vector<econSubPanel*> subPanels;

	void mouseInvoke(int mx, int my)
	{
		for (int i = 0; i < subPanels.size(); i++)
			subPanels[i]->mouseInvoke(mx, my);
	}
	void draw()
	{
		glUseProgram(shaderProgram);
		glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(300, 350, 0.0f));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-200, -300, 200, 300);

		string str = "Labor pool: ";// +std::to_string(int(sim.population.laborPool));
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
		glUseProgram(shaderProgram);
		glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(300, 350, 0.0f));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");

		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-200, -300, 200, 300);
		string str = "GDP ";// +to_string(int(sim.GDP.total));

		RenderText(fontShader, str, 120, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		//ch->data = sim.GDP.history;
		ch->draw();
	};
};




class econMenu
{
public:
	econMenu(int x, int y, int id, econPanel* panel, string text)
	{
		this->x = x + 50;
		this->y = y;
		this->id = id;
		p = panel;
		this->text = text;
	}
	string text;
	double x, y;
	int id;
	econPanel* p;
	void draw()
	{
		drawBase();
		RenderText(fontShader, text, x - 50, y - 10, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
	}
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



class economicsMenu : virtual public tab
{
public:
	std::vector<econMenu*> menus;
	economicsMenu(int x, int y)
	{
		this->x = 320;
		this->y = 980;

		menus.push_back(new econMenu(50, 800, 0, new EconPanelPrimary(), string("Primary")));
		menus.push_back(new econMenu(270, 800, 1, new EconPanelSecondary(), string("Secondary")));
		menus.push_back(new econMenu(490, 800, 2, new EconPanelTetriary(), string("Tetriary")));
		menus.push_back(new econMenu(710, 800, 3, new EconPanelReport(), string("Report")));
		
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