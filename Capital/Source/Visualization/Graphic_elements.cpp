#pragma once
#include <cstdlib> 
#include <ctime>  
#include "Visualization.h"
#include "Graphic_elements.h"
extern Visualization visualization;

int*  Panel::gs = 0;

void Technology_menu::init()
{
	int x_slot = visualization.x_slot;
	int y_slot = visualization.y_slot;
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 5, y_slot * 24);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);

}

void Goverment_menu::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 5, y_slot * 24);

	panel->add_dynamic_text_element("Workers:  ", " ",  x_slot * 4, y_slot * 17, &simulation.player.industries["Goverment"]->workforce[0].quantity);
	panel->add_dynamic_text_element("Goverment budget:  ", " ",  x_slot * 4, y_slot * 21, &simulation.player.industries["Goverment"]->revenue);

	panel->add_dynamic_text_element("Wages: ", &simulation.player.industries["Goverment"]->wages.result, x_slot * 4, y_slot * 19);
	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text);
}



void Agriculture_sector_panel :: init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot*6, y_slot * 21);



	base = (new Quad_button())->set_properties(shaderProgram, fontShader, x, y, size_x, size_y, text, 0.7);

	root_menus.push_back((new Gathering_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot*5, 700, 150, 40, "Gathering"));
	root_menus.push_back((new Farming_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 600, 150, 40, "Farming"));
	root_menus.push_back((new Husbandry_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 500, 150, 40, "Husbandry"));
	root_menus.push_back((new Forestry_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 400, 150, 40, "Forestry"));
	for (auto a : root_menus)
	{
		a->init();
	}

}
void Industry_sector_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot*6, y_slot * 21);


	
	root_menus.push_back((new Pottery_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 700, 150, 40, "Pottery"));
	root_menus.push_back((new Textile_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, 600, 150, 40, "Textile"));

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
	Industry* industry = simulation.player.industries["Construction"];
	Exchange* ex1 = simulation.player.exchanges[constr_exc];
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 20, y_slot * 21, 350);

	panel->add_dynamic_text_element("Gatherers wages: ", &industry->wages.result, x_slot * 13, y_slot * 27);

	panel->add_dynamic_text_element("Workforce: ", &industry->workforce_d.result, x_slot * 13, y_slot * 25);

	panel->add_dynamic_text_element("Revenue:  ", &industry->revenue_d.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Gross profit:  ", &industry->gross_profit_d.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Operational profit:  ", &industry->operating_profit_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Investment bank:  ", &industry->investment_account_d.result, x_slot * 13, y_slot * 17);

	panel->add_dynamic_text_element("Food price:  ", &ex1->current_price_d.result, x_slot * 13, y_slot * 15);

	panel->add_dynamic_text_element("Quantity sold:  ", &ex1->sold_quantity_d.result, x_slot * 13, y_slot * 13);

	panel->add_dynamic_text_element("Supply:  ", &ex1->total_supply_d.result, x_slot * 13, y_slot * 11);

	panel->add_dynamic_text_element("Demand:  ", &ex1->total_demand_d.result, x_slot * 13, y_slot * 9);
	
	panel->add_dynamic_text_element("Backlog:  ", &ex1->quantity_backlog_d.result, x_slot * 13, y_slot * 7);

}

void Economics_menu::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, 250, y_slot*21);

	panel->add_dynamic_text_element("MD: ", "", x, y - 250, &simulation.player.money_delta);

	panel->add_dynamic_text_element("Total wages: ", "", x, y - 300, &simulation.player.total_wages);

	panel->add_dynamic_text_element("Consumption level: ", "", x, y - 350, &simulation.player.demography.consumption_level);

	panel->add_dynamic_text_element("GDP: ", &simulation.player.GDP.total.result, x, y - 400);

	panel->add_dynamic_text_element("Delta workers: ", " D ", x_slot * 6, y - 450, &simulation.player.demography.delta_workers);

	panel->add_dynamic_text_element("Enemployed: ", " D ", x_slot * 6, y - 500, &simulation.player.industries["Unemployed"]->workforce[0].quantity);

	//panel->add_dynamic_text_element("Wheat Price: ", " Tonnes", x, y - 750, &simulation.foodExc.current_price);

	panel->add_dynamic_text_element("Agri money:  ", " Square km", x, y - 550, &simulation.player.industries["Farming"]->money);
	panel->add_dynamic_text_element("Gath money:  ", " Square km", x, y - 600, &simulation.player.industries["Gathering"]->money);
	panel->add_dynamic_text_element("Pottery money:  ", " Square km", x, y - 750, &simulation.player.industries["Pottery"]->money);
	panel->add_dynamic_text_element("Animal money:  ", " Square km", x, y - 650, &simulation.player.industries["Husbandry"]->money);
	panel->add_dynamic_text_element("Cloth money:  ", " Square km", x, y - 700, &simulation.player.industries["Textile"]->money);
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
	root_menus.push_back((new Society_demography_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, y_slot * 25, 125, 40, "Demorgaphy"));
	root_menus.push_back((new Society_profession_panel())->set_properties(&root_menus, shaderProgram, fontShader, x_slot * 5, y_slot * 20, 125, 40, "Jobs"));

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
	Industry* industry = simulation.player.industries["Gathering"];
	Exchange* ex1 = simulation.player.exchanges[food_exc];
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 20, y_slot * 21, 350);

	panel->add_dynamic_text_element("Gatherers wages: ", &industry->wages.result, x_slot * 13, y_slot * 27);

	panel->add_dynamic_text_element("Workforce: ", &industry->workforce_d.result, x_slot * 13, y_slot * 25);

	panel->add_dynamic_text_element("Revenue:  ", &industry->revenue_d.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Gross profit:  ", &industry->gross_profit_d.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Operational profit:  ", &industry->operating_profit_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Investment bank:  ", &industry->investment_account_d.result, x_slot * 13, y_slot * 17);

	panel->add_dynamic_text_element("Food price:  ", &ex1->current_price_d.result, x_slot * 13, y_slot * 15);

	panel->add_dynamic_text_element("Quantity sold:  ", &ex1->sold_quantity_d.result, x_slot * 13, y_slot * 13);

	panel->add_dynamic_text_element("Supply:  ", &ex1->total_supply_d.result, x_slot * 13, y_slot * 11);

	panel->add_dynamic_text_element("Demand:  ", &ex1->total_demand_d.result, x_slot * 13, y_slot * 9);
	
	panel->add_dynamic_text_element("Backlog:  ", &ex1->quantity_backlog_d.result, x_slot * 13, y_slot * 7);
}
void Farming_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	Industry* industry = simulation.player.industries["Farming"];
	Exchange* ex1 = simulation.player.exchanges[food_exc];
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 20, y_slot * 21, 350);

	panel->add_dynamic_text_element("Farming wages: ", &industry->wages.result, x_slot * 13, y_slot * 27);

	panel->add_dynamic_text_element("Workforce: ", &industry->workforce_d.result, x_slot * 13, y_slot * 25);

	panel->add_dynamic_text_element("Revenue:  ", &industry->revenue_d.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Gross profit:  ", &industry->gross_profit_d.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Operational profit:  ", &industry->operating_profit_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Investment bank:  ", &industry->investment_account_d.result, x_slot * 13, y_slot * 17);

	panel->add_dynamic_text_element("Food price:  ", &ex1->current_price_d.result, x_slot * 13, y_slot * 15);

	panel->add_dynamic_text_element("Quantity sold:  ", &ex1->sold_quantity_d.result, x_slot * 13, y_slot * 13);

	panel->add_dynamic_text_element("Supply:  ", &ex1->total_supply_d.result, x_slot * 13, y_slot * 11);

	panel->add_dynamic_text_element("Demand:  ", &ex1->total_demand_d.result, x_slot * 13, y_slot * 9);
	
	panel->add_dynamic_text_element("Backlog:  ", &ex1->quantity_backlog_d.result, x_slot * 13, y_slot * 7);

}

void Forestry_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	Industry* industry = simulation.player.industries["Forestry"];
	Exchange* ex1 = simulation.player.exchanges[wood_exc];
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 20, y_slot * 21, 350);

	panel->add_dynamic_text_element("Farming wages: ", &industry->wages.result, x_slot * 13, y_slot * 27);

	panel->add_dynamic_text_element("Workforce: ", &industry->workforce_d.result, x_slot * 13, y_slot * 25);

	panel->add_dynamic_text_element("Revenue:  ", &industry->revenue_d.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Gross profit:  ", &industry->gross_profit_d.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Operational profit:  ", &industry->operating_profit_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Investment bank:  ", &industry->investment_account_d.result, x_slot * 13, y_slot * 17);

	panel->add_dynamic_text_element("Food price:  ", &ex1->current_price_d.result, x_slot * 13, y_slot * 15);

	panel->add_dynamic_text_element("Quantity sold:  ", &ex1->sold_quantity_d.result, x_slot * 13, y_slot * 13);

	panel->add_dynamic_text_element("Supply:  ", &ex1->total_supply_d.result, x_slot * 13, y_slot * 11);

	panel->add_dynamic_text_element("Demand:  ", &ex1->total_demand_d.result, x_slot * 13, y_slot * 9);
	
	panel->add_dynamic_text_element("Backlog:  ", &ex1->quantity_backlog_d.result, x_slot * 13, y_slot * 7);

}

void Husbandry_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	Industry* industry = simulation.player.industries["Husbandry"];
	Exchange* ex1 = simulation.player.exchanges[wool_exc];
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 20, y_slot * 21, 350);

	panel->add_dynamic_text_element("Shepards wages: ", &industry->wages.result, x_slot * 13, y_slot * 27);

	panel->add_dynamic_text_element("Workforce: ", &industry->workforce_d.result, x_slot * 13, y_slot * 25);

	panel->add_dynamic_text_element("Revenue:  ", &industry->revenue_d.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Gross profit:  ", &industry->gross_profit_d.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Operational profit:  ", &industry->operating_profit_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Investment bank:  ", &industry->investment_account_d.result, x_slot * 13, y_slot * 17);

	panel->add_dynamic_text_element("Wool price:  ", &ex1->current_price_d.result, x_slot * 13, y_slot * 15);

	panel->add_dynamic_text_element("Quantity sold:  ", &ex1->sold_quantity_d.result, x_slot * 13, y_slot * 13);

	panel->add_dynamic_text_element("Supply:  ", &ex1->total_supply_d.result, x_slot * 13, y_slot * 11);

	panel->add_dynamic_text_element("Demand:  ", &ex1->total_demand_d.result, x_slot * 13, y_slot * 9);
	
	panel->add_dynamic_text_element("Backlog:  ", &ex1->quantity_backlog_d.result, x_slot * 13, y_slot * 7);
}
void Pottery_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	Industry* industry = simulation.player.industries["Pottery"];
	Exchange* ex1 = simulation.player.exchanges[pottery_exc];
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 20, y_slot * 21, 350);

	panel->add_dynamic_text_element("Potters wages: ", &industry->wages.result, x_slot * 13, y_slot * 27);

	panel->add_dynamic_text_element("Workforce: ", &industry->workforce_d.result, x_slot * 13, y_slot * 25);

	panel->add_dynamic_text_element("Revenue:  ", &industry->revenue_d.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Gross profit:  ", &industry->gross_profit_d.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Operational profit:  ", &industry->operating_profit_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Investment bank:  ", &industry->investment_account_d.result, x_slot * 13, y_slot * 17);

	panel->add_dynamic_text_element("Pottery price:  ", &ex1->current_price_d.result, x_slot * 13, y_slot * 15);

	panel->add_dynamic_text_element("Quantity sold:  ", &ex1->sold_quantity_d.result, x_slot * 13, y_slot * 13);

	panel->add_dynamic_text_element("Supply:  ", &ex1->total_supply_d.result, x_slot * 13, y_slot * 11);

	panel->add_dynamic_text_element("Demand:  ", &ex1->total_demand_d.result, x_slot * 13, y_slot * 9);
	
	panel->add_dynamic_text_element("Backlog:  ", &ex1->quantity_backlog_d.result, x_slot * 13, y_slot * 7);
}
void Textile_panel::init()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;
	Industry* industry = simulation.player.industries["Textile"];
	Exchange* ex1 = simulation.player.exchanges[cloth_exc];
	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 20, y_slot * 21, 350);
	//	panel->add_dynamic_text_element("MD: ", "", x, y - 250, &simulation.player.money_delta);
	panel->add_dynamic_text_element("Stockpile: ", "", x_slot * 13, y_slot * 29, &industry->stockpile);

	panel->add_dynamic_text_element("Weavers wages: ", &industry->wages.result, x_slot * 13, y_slot * 27);

	panel->add_dynamic_text_element("Workforce: ", &industry->workforce_d.result, x_slot * 13, y_slot * 25);

	panel->add_dynamic_text_element("Revenue:  ", &industry->revenue_d.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Gross profit:  ", &industry->gross_profit_d.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Operational profit:  ", &industry->operating_profit_d.result, x_slot * 13, y_slot * 19);

	panel->add_dynamic_text_element("Investment bank:  ", &industry->investment_account_d.result, x_slot * 13, y_slot * 17);

	panel->add_dynamic_text_element("Cloth price:  ", &ex1->current_price_d.result, x_slot * 13, y_slot * 15);

	panel->add_dynamic_text_element("Quantity sold:  ", &ex1->sold_quantity_d.result, x_slot * 13, y_slot * 13);

	panel->add_dynamic_text_element("Supply:  ", &ex1->total_supply_d.result, x_slot * 13, y_slot * 11);

	panel->add_dynamic_text_element("Demand:  ", &ex1->total_demand_d.result, x_slot * 13, y_slot * 9);
	
	panel->add_dynamic_text_element("Backlog:  ", &ex1->quantity_backlog_d.result, x_slot * 13, y_slot * 7);
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

	panel = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 20, y_slot * 21, 350);

	panel->add_dynamic_text_element("Cloth wages: ", &simulation.player.industries["Textile"]->wages.result, x_slot * 13, y_slot * 23);

	panel->add_dynamic_text_element("Cloth income: ", &simulation.player.industries["Textile"]->income.result, x_slot * 13, y_slot * 21);

	panel->add_dynamic_text_element("Workforce: ", &simulation.player.industries["Textile"]->workforce_d.result, x_slot * 13, y_slot * 19);

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
		std::vector<Profession> data;
	
		for (auto& t : simulation.player.industries)
			data.push_back(Profession(t.first, t.second->total_worker_count / simulation.player.demography.laborPool, t.second->color));
		chart->draw(data);
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