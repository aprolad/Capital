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
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);
	panel->add_dynamic_text_element("Goverment budget: ", &simulation.goverment.d_money.result, x_slot * 4, y_slot * 21);
	panel->add_dynamic_text_element("Wages: ", &simulation.goverment.wages.result, x_slot * 4, y_slot * 19);
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



	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text, 0.7);

	root_menus.push_back((new Gathering_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot*5, 700, 125, 40, "Gathering"));
	root_menus.push_back((new Farming_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 600, 125, 40, "Farming"));
	root_menus.push_back((new Husbandry_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 500, 125, 40, "Husbandry"));

	for (auto a : root_menus)
	{
		a->init();
	}

}
void Industry_sector_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 6, y_slot * 16);


	

	root_menus.push_back((new Pottery_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 700, 125, 40, "Pottery"));
	root_menus.push_back((new Textile_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 600, 125, 40, "Textile"));
	for (auto a : root_menus)
	{
		a->init();
	}

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
	gdp_chart = new GDP_chart(900, 900);
	gdp_chart->init();
	gdp_chart->set_properties(shaderProgram, fontShader);
}

void Society_menu::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.x / 50;


	//Wchart->set_properties(shaderProgram, fontShader);
	root_menus.push_back((new Society_demography_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 700, 125, 40, "Gathering"));
	root_menus.push_back((new Society_profession_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 600, 125, 40, "Farming"));

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, 650);
	
	for (auto a : root_menus)
	{
		a->init();
	}
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
}

void Gathering_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Gatherers wages: ", &simulation.gathering.wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Gathering income: ", &simulation.gathering.income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.gathering.workforce.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Food price:  ", " ", x_slot * 13, y_slot * 17, &simulation.foodExc.current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.foodExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.foodExc.total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.foodExc.quantity_backlog);
}
void Farming_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Farming wages: ", &simulation.agriculture.wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Farming income: ", &simulation.agriculture.income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.agriculture.workforce.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Food price:  ", " ", x_slot * 13, y_slot * 17, &simulation.foodExc.current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.foodExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.foodExc.total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.foodExc.quantity_backlog);
}
void Husbandry_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Wool wages: ", &simulation.husbandry.wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Wool income: ", &simulation.husbandry.income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.husbandry.workforce.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Wool price:  ", " ", x_slot * 13, y_slot * 17, &simulation.woolExc.current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.woolExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.woolExc.total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.woolExc.quantity_backlog);
}
void Pottery_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Pottery wages: ", &simulation.pottery.wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Pottry income: ", &simulation.pottery.income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.pottery.workforce.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Pottery price:  ", " ", x_slot * 13, y_slot * 17, &simulation.potteryExc.current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.potteryExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.potteryExc.total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.potteryExc.quantity_backlog);
}
void Textile_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Cloth wages: ", &simulation.textile.wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Cloth income: ", &simulation.textile.income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.textile.workforce.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Cloth price:  ", " ", x_slot * 13, y_slot * 17, &simulation.clothExc.current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.clothExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.clothExc.total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.clothExc.quantity_backlog);
}

void Society_demography_panel::init()
{
	chart = new Age_chart(shaderProgram, fontShader);
	chart->init();
	chart->set_properties(shaderProgram, fontShader);
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 250);

	panel->add_dynamic_text_element("Cloth wages: ", &simulation.textile.wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Cloth income: ", &simulation.textile.income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.textile.workforce.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Cloth price:  ", " ", x_slot * 13, y_slot * 17, &simulation.clothExc.current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.clothExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.clothExc.total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.clothExc.quantity_backlog);
}

void Society_demography_panel::draw()
{
		draw_button();
		if (active)
		{
			panel->draw();
			for (auto a : root_menus)
				a->draw();
			chart->draw(std::vector(simulation.population.agePyramid.begin() + 1, simulation.population.agePyramid.end()));
		}
}

void Society_profession_panel::init()
{
	chart = new Pie_chart(shaderProgram, fontShader, 1500, 900);
	chart->init();
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Cloth wages: ", &simulation.textile.wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Cloth income: ", &simulation.textile.income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.textile.workforce.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Cloth price:  ", " ", x_slot * 13, y_slot * 17, &simulation.clothExc.current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.clothExc.total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.clothExc.total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.clothExc.quantity_backlog);
}

void Society_profession_panel::draw()
{
	draw_button();
	if (active)
	{
		panel->draw();
		for (auto a : root_menus)
			a->draw();
		//chart->draw(std::vector(simulation.population.agePyramid.begin() + 1, simulation.population.agePyramid.end()));
		chart->draw(simulation.socium.worker_types);
	}
}