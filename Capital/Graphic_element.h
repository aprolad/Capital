#pragma once
#include "Header.h"
#include "game/simulation.h"
#include "AMGUI/AMGUI.h"


extern Simulation simulation;

class Demographics_menu : virtual public Multiple_choice_panel
{
public:
	ageChart* chart;
	void draw()
	{

		draw_button();
		if (active)
		{
			panel->draw();
			chart->draw(std::vector(simulation.population.agePyramid.begin()+1, simulation.population.agePyramid.end()));
		}
	}
	void init();
};

class Technology_menu : virtual public Multiple_choice_panel
{
public:

	void init();
	void draw()
	{
		draw_button();
		if (active)
		{
			panel->draw();
		}

	}
};

class Goverment_menu : virtual public Multiple_choice_panel
{
public:

	void init();
	void draw()
	{
		draw_button();

		if (active)
		{
			panel->draw();
		}

	}
};

class Panel : virtual public Graphic_element
{
public:
	void mouseCallback(double mx, double my)
	{
		if (mx > (x - size_x) && mx < (x + size_x) && my >(y - size_y) && my < (y + size_y))
			for (auto a : buttons)
				a.mouseCallback(mx, my);
	}
	Quad_button buttons[3];
	static int* gs;
	Panel* set_properties(GLuint shader, GLuint font, int ax, int ay, int sx, int sy)
	{
		shaderProgram = shader;
		fontShader = font;
		x = ax;
		y = ay;
		size_x = sx;
		size_y = sy;
		init();
		gs = &simulation.game_speed;
		buttons[0] = *(new Quad_button())->set_properties(shaderProgram, fontShader, x - 40, 1250, 19, 20, "1");
		buttons[0].text_color = { 1,0,0 };
		buttons[0].action = []() -> void { *gs = 1; };
		buttons[1] = *(new Quad_button())->set_properties(shaderProgram, fontShader, x, 1250, 20, 19, "2");
		buttons[1].text_color = { 1,1,0 };
		buttons[1].action = []() -> void { *gs = 10; };
		buttons[2] = *(new Quad_button())->set_properties(shaderProgram, fontShader, x + 40, 1250, 19, 20, "3");
		buttons[2].text_color = { 0,1,0 };
		buttons[2].action = []() -> void { *gs = 100; };
		return this;
	}
	
	void draw()
	{

		prepare_shaders();
		
		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.3, 0.3, 0, 1);
		for (auto a : buttons)
			a.draw();
		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0, 1);
	}
};


class Agriculture_panel : virtual public Multiple_choice_panel
{
public:
	void draw()
	{
		draw_button();

		if (active)
		{
			panel->draw();
		}

	}
};
class Agriculture_sector_panel : virtual public Agriculture_panel
{
public:
	void init();

};

class Economics_menu : virtual public Multiple_choice_panel
{
public:
	std::vector<Multiple_choice_panel*> root_menus;
	Chart* chartG;
	void init();

	void mouseCallback(double mx, double my)
	{
		for (auto a : root_menus)
		{
			a->mouseCallback(mx, my);
		}
		if (mx > (x - size_x) && mx < (x + size_x) && my >(y - size_y) && my < (y + size_y))
		{
			bool t = active;
			for (int i = 0; i < top_menus->size(); i++)
			{
				(top_menus->at(i))->active = false;
			}
			active = !t;
		}
	}
	void draw()
	{
		draw_button();

		if (active)
		{
			bool has_true = std::any_of(root_menus.begin(), root_menus.end(), [this](const Multiple_choice_panel* obj) {return obj->active; });
			if (!has_true)
				panel->draw();
			chartG->draw(simulation.GDP.history);

			for (auto a : root_menus)
				a->draw();
		}

	}
};