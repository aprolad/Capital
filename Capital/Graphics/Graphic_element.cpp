#pragma once

#include "../Visualization.h"
//#include "Graphic_element.h"
extern Visualization visualization;
int*  Panel::gs = 0;

void Technology_menu::init()
{
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);

}

void Goverment_menu::init()
{
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);
	panel->add_dynamic_text_element("Wheat: ", "Kg", x, y - 650, &simulation.agriculture->output);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
}

void Agriculture_sector_panel :: init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot*6, y_slot * 16);

	panel->add_dynamic_text_element("GDPM: ", " Denarius", x_slot * 6, y - 400, &simulation.GDP.total);

	panel->add_dynamic_text_element("WheatM: ", " Tonnes", x_slot * 6, y - 450, &simulation.agriculture->t);

	panel->add_dynamic_text_element("TotalM arable land:  ", " Square km", x_slot * 6, y - 550, &simulation.geo.totalArableLand);

	panel->add_dynamic_text_element("Wheat outpuMt: ", " Tonnes", x_slot * 6, y - 650, &simulation.agriculture->outputT);

	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text, 0.7);

}

void Economics_menu::init()
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

void Demographics_menu::init()
{
	chart = new ageChart(2000, 120);
	chart->init();
	chart->set_properties(shaderProgram, fontShader);
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);
	panel->add_dynamic_text_element("Population: ", " ", 250, y - 400, &simulation.population.population);
	panel->add_dynamic_text_element("Labor pool: ", "", 250, y - 450, &simulation.population.laborPool);
	panel->add_dynamic_text_element("Food supply: ", "%", 250, y - 500, &simulation.population.foodSupply);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
}