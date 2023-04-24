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

void Geography_menu::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 6, y_slot * 16);



	panel->add_dynamic_text_element("Total controlled area: ", &simulation.geo.square_kilometres.result, x_slot * 6, visualization.window_resolution.y - 500);

	panel->add_dynamic_text_element("Arable area: ", &simulation.geo.totalArableLand.result, x_slot * 6, visualization.window_resolution.y - 600);

	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text, 0.7);
}


void Agriculture_sector_panel :: init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot*6, y_slot * 16);

	panel->add_dynamic_text_element("GDPM: ", " Denarius", x_slot * 6, y - 400, &simulation.GDP.total);

	panel->add_dynamic_text_element("Farmer wages: ", &simulation.agriculture.wages.result, x_slot * 6, y - 450);

	panel->add_dynamic_text_element("Gatherers wages: ", &simulation.gathering.wages.result, x_slot * 6, y - 500);

	panel->add_dynamic_text_element("Backlog:  ", " ", x_slot * 6, y - 750, &simulation.foodExc.quantity_backlog);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 6, y - 550, &simulation.foodExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 6, y - 650, &simulation.foodExc.total_demand);

	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text, 0.7);

}
void Industry_sector_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 6, y_slot * 16);


	panel->add_dynamic_text_element("Supply cloth: ", " Denarius", x_slot * 6, y - 300, &simulation.clothExc.total_supply);

	panel->add_dynamic_text_element("Demand cloth: ", " Tonnes", x_slot * 6, y - 350, &simulation.clothExc.total_demand);

	panel->add_dynamic_text_element("Supply: ", " Denarius", x_slot * 6, y - 400, &simulation.woolExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " Tonnes", x_slot * 6, y - 450, &simulation.woolExc.total_demand);

	panel->add_dynamic_text_element("Backlog:  ", " ", x_slot * 6, y - 550, &simulation.woolExc.quantity_backlog);

	panel->add_dynamic_text_element("Cloth Price: ", " ", x_slot * 6, y - 700, &simulation.clothExc.current_price);

	panel->add_dynamic_text_element("Wool demand ", " ", x_slot * 6, y - 650, &simulation.woolExc.total_demand);

	panel->add_dynamic_text_element("Workers: ", " ", x_slot * 6, y - 750, &simulation.pottery.workforce);

	panel->add_dynamic_text_element("Wage textile: ", " ", x_slot * 6, y - 800, &simulation.textile.wages);
	panel->add_dynamic_text_element("Wage wool: ", " ", x_slot * 6, y - 850, &simulation.husbandry.wages);


	panel->add_dynamic_text_element("WOOL workers: ", " ", x_slot * 6, y - 900, &simulation.husbandry.workforce);


	panel->add_dynamic_text_element("Textile workers: ", " ", x_slot * 6, y - 950, &simulation.textile.workforce);

	panel->add_dynamic_text_element("Total money: ", &simulation.population.money.result, x_slot * 6, y - 1000);

	panel->add_dynamic_text_element("Price wool: ", " ", x_slot * 6, y - 1050, &simulation.woolExc.current_price);

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

	//panel->add_dynamic_text_element("Wheat Price: ", " Tonnes", x, y - 750, &simulation.foodExc.current_price);

	panel->add_dynamic_text_element("Agri money:  ", " Square km", x, y - 550, &simulation.agriculture.money);
	panel->add_dynamic_text_element("Gath money:  ", " Square km", x, y - 600, &simulation.gathering.money);
	panel->add_dynamic_text_element("Pottery money:  ", " Square km", x, y - 750, &simulation.pottery.money);
	panel->add_dynamic_text_element("Animal money:  ", " Square km", x, y - 650, &simulation.husbandry.money);
	panel->add_dynamic_text_element("Cloth money:  ", " Square km", x, y - 700, &simulation.textile.money);
	panel->add_dynamic_text_element("Pottery: ", &simulation.population.money.result, x, y - 950);
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