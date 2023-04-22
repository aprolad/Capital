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
	panel->add_dynamic_text_element("Wheat: ", "Kg", x, y - 650, &simulation.agriculture.output);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
}

void Agriculture_sector_panel :: init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot*6, y_slot * 16);

	panel->add_dynamic_text_element("GDPM: ", " Denarius", x_slot * 6, y - 400, &simulation.GDP.total);

	panel->add_dynamic_text_element("Farmer wages: ", &simulation.agriculture.wages.result, x_slot * 6, y - 450);

	panel->add_dynamic_text_element("Gatherers wages: ", &simulation.gathering.wages.result, x_slot * 6, y - 500);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 6, y - 550, &simulation.foodExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 6, y - 650, &simulation.foodExc.total_demand);

	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text, 0.7);

}
void Industry_sector_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 6, y_slot * 16);

	panel->add_dynamic_text_element("Supply: ", " Denarius", x_slot * 6, y - 400, &simulation.potteryExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " Tonnes", x_slot * 6, y - 450, &simulation.potteryExc.total_demand);

	panel->add_dynamic_text_element("Backlog:  ", " ", x_slot * 6, y - 550, &simulation.potteryExc.quantity_backlog);

	panel->add_dynamic_text_element("Wages: ", " ", x_slot * 6, y - 650, &simulation.pottery.wages.result);

	panel->add_dynamic_text_element("Workers: ", " ", x_slot * 6, y - 750, &simulation.pottery.workforce);

	panel->add_dynamic_text_element("MS: ", " ", x_slot * 6, y - 850, &simulation.g);

	panel->add_dynamic_text_element("Income: ", " ", x_slot * 6, y - 900, &simulation.population.income);

	panel->add_dynamic_text_element("Total money: ", &simulation.population.money.result, x_slot * 6, y - 1000);

	panel->add_dynamic_text_element("Price: ", " ", x_slot * 6, y - 950, &simulation.potteryExc.current_price);

	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text, 0.7);

}

void Service_sector_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 6, y_slot * 16);

	panel->add_dynamic_text_element("GDPM: ", " Denarius", x_slot * 6, y - 400, &simulation.GDP.total);

	panel->add_dynamic_text_element("WheatM: ", " Tonnes", x_slot * 6, y - 450, &simulation.foodExc.total_supply);

	panel->add_dynamic_text_element("TotalM arable land:  ", " Square km", x_slot * 6, y - 550, &simulation.geo.totalArableLand);

	panel->add_dynamic_text_element("Wheat outpuMt: ", &simulation.agriculture.output.result, x_slot * 6, y - 650);

	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text, 0.7);

}

void Economics_menu::init()
{

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);

	panel->add_dynamic_text_element("GDP: ", &simulation.GDP.total.result, x, y - 400);

	panel->add_dynamic_text_element("Wheat: ", " Tonnes", x, y - 450, &simulation.agriculture.output.result);

	panel->add_dynamic_text_element("Wheat Price: ", " Tonnes", x+600, y - 450, &simulation.foodExc.current_price);

	panel->add_dynamic_text_element("Total arable land:  ", " Square km", x, y - 550, &simulation.agriculture.income);

	panel->add_dynamic_text_element("Wheat output: ", &simulation.population.money.result, x, y - 650);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);

	root_menus.push_back((new Agriculture_sector_panel())->set_properties(&root_menus, shaderProgram, fontShader, 200, 1100, 125, 40, "Agriculture"));
	root_menus.push_back((new Industry_sector_panel())->set_properties(&root_menus, shaderProgram, fontShader, 500, 1100, 125, 40, "Industry"));
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
	Wchart = new Pie_chart(shaderProgram, fontShader);
	Wchart->init();
	//Wchart->set_properties(shaderProgram, fontShader);
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);
	panel->add_dynamic_text_element("Population: ", " ", 250, y - 400, &simulation.population.population);
	panel->add_dynamic_text_element("Labor pool: ", "", 250, y - 450, &simulation.population.laborPool);
	panel->add_dynamic_text_element("Gatherers: ", "", 250, y - 550, &simulation.gathering.workforce);
	panel->add_dynamic_text_element("Goverment: ", "", 250, y - 650, &simulation.goverment.workforce);
	panel->add_dynamic_text_element("Food supply: ", "%", 250, y - 500, &simulation.population.foodSupply);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
}