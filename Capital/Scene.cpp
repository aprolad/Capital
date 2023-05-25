#pragma once
#include "Scene.h"
#include "Visualization.h"

extern Visualization visualization;
extern Simulation simulation;
void MainMenuScene :: construct_scene()
{
	int x_slot = visualization.window_resolution.x / 50;
	Quad_button* t = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot*5, 150, x_slot * 3, 50, "Exit");
	graphic_elements.push_back(t);
	graphic_elements[0]->action = []() -> void { exit(0); };


	t = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot * 5, 480, x_slot * 3, 50, "Start");
	graphic_elements.push_back(t);
	graphic_elements[1]->action = []() -> void { *choosen_scene = 1; };

	t = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot * 5, 260, x_slot * 3, 50, "Settings");
	graphic_elements.push_back(t);
	graphic_elements[2]->action = []() -> void { *choosen_scene = 2; };

	t = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot * 5, 370, x_slot * 3, 50, "Load game");
	graphic_elements.push_back(t);
	graphic_elements[3]->action = []() -> void { *choosen_scene = 1; };

}

void SettingsMenuScene::construct_scene()
{
	Quad_button* t = (new Quad_button())->set_properties(shaderProgram, fontShader, visualization.window_resolution.x / 10, 150, 100, 50, "Return");
	graphic_elements.push_back(t);
	graphic_elements[0]->action = []() -> void { *choosen_scene = 0; };

	t = (new Quad_button())->set_properties(shaderProgram, fontShader, visualization.window_resolution.x / 10 * 3, 150, 100, 50, "VSYNC");
	graphic_elements.push_back(t);
	graphic_elements[1]->action = []() -> void { *choosen_scene = 0; };
}

void MainGameScene::construct_scene()
{
	int x_slot = visualization.window_resolution.x / 50;
	int y_slot = visualization.window_resolution.y / 50;

	map.shaderProgram = shaderProgram;
	map.fontShader = fontShader;
	map.init();



	Quad_button* return_button = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot * 5, y_slot * 2, 100, 50, "Return");
	return_button->action = []() -> void { *choosen_scene = 0; };
	graphic_elements.push_back(return_button);





	root_menus.push_back((new Economics_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 5, y_slot * 45, 150, 50, "Economics"));

	root_menus.push_back((new Society_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 13, y_slot * 45, 150, 50, "Socio"));

	root_menus.push_back((new Technology_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 21, y_slot * 45, 150, 50, "Technology"));

	root_menus.push_back((new Geography_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 35, 150, 150, 50, "Geography"));

	root_menus.push_back((new Goverment_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 29, y_slot * 45, 150, 50, "Goverment"));

	en = (new Information_panel())->set_properties(shaderProgram, fontShader, x_slot * 46, y_slot * 16);

	en->add_dynamic_text_element("GDP: ", &simulation.enemy.GDP.total.result, x_slot * 42, y_slot * 23);

	en->add_dynamic_text_element("Population: ", " ", x_slot * 42, y_slot * 24, &simulation.enemy.demography.population);


	Dynamic_text_element<int*>* at = (new Dynamic_text_element<int*>())->set_properties(&simulation.date.calendar_years, shaderProgram, fontShader, x_slot * 45, y_slot * 48, "Date: ", simulation.date.postfix);


	graphic_elements.push_back(at);



	Panel* speed_choice_panel = (new Panel())->set_properties(shaderProgram, fontShader, x_slot * 45, y_slot * 45, 145, 25);
	graphic_elements.push_back(speed_choice_panel);

	for (int i = 0; i < root_menus.size(); i++)
	{
		graphic_elements.push_back(root_menus[i]);
	}

}