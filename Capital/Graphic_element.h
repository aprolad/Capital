#pragma once
#include "Header.h"
#include "Game/simulation.h"
#include "AMGUI/AMGUI.h"


extern Simulation simulation;

class Demographics_menu : virtual public Multiple_choice_panel
{
public:
	ageChart* chart;
	Pie_chart* Wchart;

	void draw()
	{

		draw_button();
		if (active)
		{
			panel->draw();
			//chart->draw(std::vector(simulation.population.agePyramid.begin()+1, simulation.population.agePyramid.end()));
			Wchart->draw(simulation.socium.worker_types);
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

class Geography_menu : virtual public Multiple_choice_panel
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
		buttons[0] = *(new Quad_button())->set_properties(shaderProgram, fontShader, x - 105, 1250, 40, 25, "x1");
		buttons[0].text_color = { 1,0,0 };
		buttons[0].action = []() -> void { *gs = 1; };
		buttons[1] = *(new Quad_button())->set_properties(shaderProgram, fontShader, x - 10, 1250, 55, 25, "x10");
		buttons[1].text_color = { 1,0,0 };
		buttons[1].action = []() -> void { *gs = 10; };
		buttons[2] = *(new Quad_button())->set_properties(shaderProgram, fontShader, x + 110, 1250, 60, 25, "x100");
		buttons[2].text_color = { 1,0,0 };
		buttons[2].action = []() -> void { *gs = 100; };
		return this;
	}
	
	void draw()
	{

		prepare_shaders();
		
		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0, 1);
		for (int i = 0; i < 3; i++)
		{
			buttons[i].button_color = glm::vec3(0, 0.0, 0.0);
			buttons[i].text_color = glm::vec3(1, 0.0, 0);
			if (*gs == 1)
			{
				buttons[0].text_color = glm::vec3(0, 0.0, 0);
				buttons[0].button_color = glm::vec3(0.5, 0.5, 1);
			}
			if (*gs == 10)
			{
				buttons[1].text_color = glm::vec3(0, 0.0, 0);
				buttons[1].button_color = glm::vec3(0.5, 0.5, 1);
			}
			if (*gs == 100)
			{
				buttons[2].text_color = glm::vec3(0, 0.0, 0);
				buttons[2].button_color = glm::vec3(0.5, 0.5, 1);
			}

				glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0, 1);
			buttons[i].draw();
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 1.0, 0.0, 0, 1);
		}
		glUseProgram(shaderProgram);
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0, 1);
	}
};


class Economy_panel : virtual public Multiple_choice_panel
{
public:
	void draw()
	{
		draw_button();

		if (active)
		{
			panel->draw();
			for (auto a : root_menus)
				a->draw();
		}

	}
};
class Agriculture_sector_panel : virtual public Economy_panel
{
public:
	void init();
	
};

class Industry_sector_panel : virtual public Economy_panel
{
public:
	void init();
};
class Service_sector_panel : virtual public Economy_panel
{
public:
	void init();
};

class Economics_menu : virtual public Multiple_choice_panel
{
public:
	Chart* chartG;
	void init();

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

class Farming_panel : virtual public Economy_panel
{
public:
	void init();
};
class Husbandry_panel : virtual public Economy_panel
{
public:
	void init();
};
class Gathering_panel : virtual public Economy_panel
{
public:
	void init();
};

class Pottery_panel : virtual public Economy_panel
{
public:
	void init();
};
class Textile_panel : virtual public Economy_panel
{
public:
	void init();
};