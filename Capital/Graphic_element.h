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
	void init()
	{
		chart = new ageChart(2000, 120);
		chart->init();
		chart->set_properties(shaderProgram, fontShader);
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);
		panel->add_dynamic_text_element("Population: "," ", 250, y - 400, &simulation.population.population);
		panel->add_dynamic_text_element("Labor pool: ","", 250, y - 450, &simulation.population.laborPool);
		panel->add_dynamic_text_element("Food supply: ","%", 250, y - 500, &simulation.population.foodSupply);
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
	}
};

class Technology_menu : virtual public Multiple_choice_panel
{
public:

	Chart* chartG;
	void init()
	{
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);

		
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
		
	}
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

	Chart* chartG;
	void init()
	{
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);

		panel->add_dynamic_text_element("Wheat: ", "Kg" , x, y - 650, &simulation.agriculture->output);
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
	
	}
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
		buttons[0] = *(new Quad_button())->set_properties(shaderProgram, fontShader, 2005, 1250, 20, 20, "1");
		buttons[0].text_color = { 1,0,0 };
		buttons[0].action = []() -> void { *gs = 1; };
		buttons[1] = *(new Quad_button())->set_properties(shaderProgram, fontShader, 2050, 1250, 20, 20, "2");
		buttons[1].text_color = { 1,1,0 };
		buttons[1].action = []() -> void { *gs = 10; };
		buttons[2] = *(new Quad_button())->set_properties(shaderProgram, fontShader, 2095, 1250, 20, 20, "3");
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

	void init()
	{
		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 150, 150);

		panel->add_dynamic_text_element("GDPM: ", " Denarius", x, y - 400, &simulation.GDP.total);

		panel->add_dynamic_text_element("WheatM: ", " Tonnes", x, y - 450, &simulation.agriculture->t);

		panel->add_dynamic_text_element("TotalM arable land:  ", " Square km", x, y - 550, &simulation.geo.totalArableLand);

		panel->add_dynamic_text_element("Wheat outpuMt: ", " Tonnes", x, y - 650, &simulation.agriculture->outputT);
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
	
	}

};

class Economics_menu : virtual public Multiple_choice_panel
{
public:
	std::vector<Multiple_choice_panel*> root_menus;
	Chart* chartG;
	void init()
	{
		


		panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);

		panel->add_dynamic_text_element("GDP: ", " Denarius", x, y - 400, &simulation.GDP.total);

		panel->add_dynamic_text_element("Wheat: ", " Tonnes", x, y - 450, &simulation.agriculture->t);

		panel->add_dynamic_text_element("Total arable land:  ", " Square km", x, y - 550, &simulation.geo.totalArableLand);

		panel->add_dynamic_text_element("Wheat output: ", " Tonnes", x, y - 650, &simulation.agriculture->outputT);
		base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);

		root_menus.push_back((new Agriculture_sector_panel())->set_properties(&root_menus, shaderProgram, fontShader, 200, 1100, 125, 40, "Agriculture"));
		root_menus.push_back((new Agriculture_sector_panel())->set_properties(&root_menus, shaderProgram, fontShader, 500, 1100, 125, 40, "Industry"));
		root_menus.push_back((new Agriculture_sector_panel())->set_properties(&root_menus, shaderProgram, fontShader, 800, 1100, 125, 40, "Services"));
		for (auto a : root_menus)
		{
			a->init();
		}

		chartG = new Chart(900, 900);
		chartG->init();
		chartG->set_properties(shaderProgram, fontShader);
	}
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

			panel->draw();
			chartG->draw(simulation.GDP.history);

			for (auto a : root_menus)
				a->draw();
		}

	}
};