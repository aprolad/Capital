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

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 5, y_slot * 24);

	panel->add_dynamic_text_element("Workers:  ", " ",  x_slot * 4, y_slot * 17, &simulation.player.industries[goverment]->workforce);
	panel->add_dynamic_text_element("Goverment budget:  ", " ",  x_slot * 4, y_slot * 21, &simulation.player.industries[goverment]->money);

	panel->add_dynamic_text_element("Wages: ", &simulation.player.industries[goverment]->wages.result, x_slot * 4, y_slot * 19);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
}

void Geography_menu::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 6, y_slot * 16);



	panel->add_dynamic_text_element("Total controlled area: ", &simulation.player.geography.square_kilometres.result, x_slot * 6, visualization.window_resolution.y - 500);

	panel->add_dynamic_text_element("Arable area: ", &simulation.player.geography.totalArableLand.result, x_slot * 6, visualization.window_resolution.y - 600);

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

	panel->add_dynamic_text_element("Wages constr: ", " Denarius", x_slot * 6, y - 400, &simulation.player.industries[construction]->wages);

	panel->add_dynamic_text_element("Demand: ", " Tonnes", x_slot * 6, y - 450, &simulation.player.exchanges[constr_exc]->total_demand);

	panel->add_dynamic_text_element("Supply: ", " Tonnes", x_slot * 6, y - 500, &simulation.player.exchanges[constr_exc]->total_supply);

	panel->add_dynamic_text_element("Revenue:  ", " Square km", x_slot * 6, y - 550, &simulation.player.industries[construction]->revenue);

	panel->add_dynamic_text_element("Wheat outpuMt: ", &simulation.player.industries[0]->output.result, x_slot * 6, y - 650);

	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text, 0.7);

}

void Economics_menu::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, y_slot*25);

	panel->add_dynamic_text_element("GDP: ", &simulation.player.GDP.total.result, x, y - 400);

	panel->add_dynamic_text_element("Delta workers: ", " D ", x_slot * 6, y - 450, &simulation.player.demography.delta_workers);

	panel->add_dynamic_text_element("Enemployed: ", " D ", x_slot * 6, y - 500, &simulation.player.industries[unemployed]->workforce);

	//panel->add_dynamic_text_element("Wheat Price: ", " Tonnes", x, y - 750, &simulation.foodExc.current_price);

	panel->add_dynamic_text_element("Agri money:  ", " Square km", x, y - 550, &simulation.player.industries[farming]->money);
	panel->add_dynamic_text_element("Gath money:  ", " Square km", x, y - 600, &simulation.player.industries[gathering]->money);
	panel->add_dynamic_text_element("Pottery money:  ", " Square km", x, y - 750, &simulation.player.industries[pottery]->money);
	panel->add_dynamic_text_element("Animal money:  ", " Square km", x, y - 650, &simulation.player.industries[husbandry]->money);
	panel->add_dynamic_text_element("Cloth money:  ", " Square km", x, y - 700, &simulation.player.industries[textile]->money);
	panel->add_dynamic_text_element("pop money: ", &simulation.player.demography.money.result, x, y - 950);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);

	root_menus.push_back((new Agriculture_sector_panel())->set_properties(&root_menus, shaderProgram, fontShader, 200, y_slot * 40, 125, 40, "Agriculture"));
	root_menus.push_back((new Industry_sector_panel())->set_properties(&root_menus, shaderProgram, fontShader, 500, y_slot * 40, 125, 40, "Industry"));
	root_menus.push_back((new Service_sector_panel())->set_properties(&root_menus, shaderProgram, fontShader, 800, y_slot * 40, 125, 40, "Services"));
	for (auto a : root_menus)
	{
		a->init();
	}
	gdp_chart = new GDP_chart(x_slot*14, y_slot*22);
	gdp_chart->init();
	gdp_chart->set_properties(shaderProgram, fontShader);
}

void Society_menu::init()
{
	int x_slot = visualization.x_slot;
	int y_slot = visualization.y_slot;


	//Wchart->set_properties(shaderProgram, fontShader);
	root_menus.push_back((new Society_demography_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 4, y_slot * 25, 125, 40, "Demorgaphy"));
	root_menus.push_back((new Society_profession_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 4, y_slot * 20, 125, 40, "Jobs"));

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, y_slot * 24);
	
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

	panel->add_dynamic_text_element("Gatherers wages: ", &simulation.player.industries[gathering]->wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Gathering income: ", &simulation.player.industries[gathering]->income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.player.industries[gathering]->workforce_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Food price:  ", " ", x_slot * 13, y_slot * 17, &simulation.player.exchanges[food_exc]->current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.player.exchanges[food_exc]->total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.player.exchanges[food_exc]->total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.player.exchanges[food_exc]->quantity_backlog);
}
void Farming_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Investment bank: ", " ", x_slot * 13, y_slot * 27, &simulation.player.industries[farming]->investment_account);

	panel->add_dynamic_text_element("Farming wages: ", &simulation.player.industries[farming]->wages.result, x_slot * 13, y_slot * 25);

	panel->add_dynamic_text_element("Operating profit: ", " ", x_slot * 13, y_slot * 23, &simulation.player.industries[farming]->operating_profit);

	panel->add_dynamic_text_element("Revenue:  ", " ", x_slot * 13, y_slot * 21, &simulation.player.industries[farming]->revenue);

	panel->add_dynamic_text_element("Workforce: ", &simulation.player.industries[farming]->workforce_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Food price:  ", " ", x_slot * 13, y_slot * 17, &simulation.player.exchanges[food_exc]->current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.player.exchanges[food_exc]->total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.player.exchanges[food_exc]->total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.player.exchanges[food_exc]->quantity_backlog);
}
void Husbandry_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Wool wages: ", &simulation.player.industries[husbandry]->wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Wool income: ", &simulation.player.industries[husbandry]->income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.player.industries[husbandry]->workforce_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Wool price:  ", " ", x_slot * 13, y_slot * 17, &simulation.player.exchanges[wool_exc]->current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.player.exchanges[wool_exc]->total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.player.exchanges[wool_exc]->total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.player.exchanges[wool_exc]->quantity_backlog);
}
void Pottery_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Pottery wages: ", &simulation.player.industries[pottery]->wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Pottry income: ", &simulation.player.industries[pottery]->income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.player.industries[pottery]->workforce_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Pottery price:  ", " ", x_slot * 13, y_slot * 17, &simulation.player.exchanges[pottery_exc]->current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.player.exchanges[pottery_exc]->total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.player.exchanges[pottery_exc]->total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.player.exchanges[pottery_exc]->quantity_backlog);
}
void Textile_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Cloth wages: ", &simulation.player.industries[textile]->wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Cloth income: ", &simulation.player.industries[textile]->income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.player.industries[textile]->workforce_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Cloth price:  ", " ", x_slot * 13, y_slot * 17, &simulation.player.exchanges[cloth_exc]->current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.player.exchanges[cloth_exc]->total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.player.exchanges[cloth_exc]->total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.player.exchanges[cloth_exc]->quantity_backlog);
}

void Society_demography_panel::init()
{
	chart = new Age_chart(1200, 100);
	chart->init();
	chart->set_properties(shaderProgram, fontShader);
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 250);


}

void Society_demography_panel::draw()
{
		draw_button();
		if (active)
		{
			//panel->draw();
			for (auto a : root_menus)
				a->draw();
			chart->draw(std::vector(simulation.player.demography.agePyramid.begin() + 1, simulation.player.demography.agePyramid.end()));
		}
}

void Society_profession_panel::init()
{
	int x_slot = visualization.y_slot;
	int y_slot = visualization.x_slot;
	chart = new Pie_chart(shaderProgram, fontShader, x_slot * 35, y_slot * 15);
	chart->init();

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 16, y_slot * 16, 400);

	panel->add_dynamic_text_element("Cloth wages: ", &simulation.player.industries[textile]->wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Cloth income: ", &simulation.player.industries[textile]->income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.player.industries[textile]->workforce_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Cloth price:  ", " ", x_slot * 13, y_slot * 17, &simulation.player.exchanges[cloth_exc]->current_price);

	panel->add_dynamic_text_element("Supply:  ", " ", x_slot * 13, y_slot * 15, &simulation.player.exchanges[cloth_exc]->total_supply);

	panel->add_dynamic_text_element("Demand: ", " ", x_slot * 13, y_slot * 13, &simulation.player.exchanges[cloth_exc]->total_demand);

	panel->add_dynamic_text_element("Backlog: ", " ", x_slot * 13, y_slot * 11, &simulation.player.exchanges[cloth_exc]->quantity_backlog);
}

void Society_profession_panel::draw()
{
	draw_button();
	if (active)
	{
		//panel->draw();
		for (auto a : root_menus)
			a->draw();
		//chart->draw(std::vector(simulation.population.agePyramid.begin() + 1, simulation.population.agePyramid.end()));
		chart->draw(simulation.player.socium.worker_types);
	}
}

Panel* Panel::set_properties(GLuint shader, GLuint font, int ax, int ay, int sx, int sy)
{

	shaderProgram = shader;
	fontShader = font;
	x = ax;
	y = ay;
	size_x = sx;
	size_y = sy;
	init();
	gs = &simulation.game_speed;
	buttons[0] = *(new Quad_button())->set_properties(shaderProgram, fontShader, x - 105, visualization.y_slot*45, 40, 25, "x1");
	buttons[0].text_color = { 1,0,0 };
	buttons[0].action = []() -> void { *gs = 1; };
	buttons[1] = *(new Quad_button())->set_properties(shaderProgram, fontShader, x - 10, visualization.y_slot * 45, 55, 25, "x10");
	buttons[1].text_color = { 1,0,0 };
	buttons[1].action = []() -> void { *gs = 10; };
	buttons[2] = *(new Quad_button())->set_properties(shaderProgram, fontShader, x + 110, visualization.y_slot * 45, 60, 25, "x100");
	buttons[2].text_color = { 1,0,0 };
	buttons[2].action = []() -> void { *gs = 100; };
	return this;
}