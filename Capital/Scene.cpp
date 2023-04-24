#pragma once
#include "Scene.h"
#include "Visualization.h"

extern Visualization visualization;
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
	map.shaderProgram = shaderProgram;
	map.init();

	Quad_button* t = (new Quad_button())->set_properties(shaderProgram, fontShader, visualization.window_resolution.x / 10, 150, 100, 50, "Return");
	graphic_elements.push_back(t);
	graphic_elements[0]->action = []() -> void { *choosen_scene = 0; };


	root_menus.push_back((new Economics_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.window_resolution.x / 20 * 2, 1270, 150, 50, "Economics"));

	root_menus.push_back((new Demographics_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.window_resolution.x / 20 * 5, 1270, 150, 50, "Socio"));

	root_menus.push_back((new Technology_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.window_resolution.x / 20 * 8, 1270, 150, 50, "Technology"));

	root_menus.push_back((new Geography_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.window_resolution.x / 20 * 11, 150, 150, 50, "Geography"));

	root_menus.push_back((new Goverment_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.window_resolution.x / 20 * 11, 1270, 150, 50, "Goverment"));



	Dynamic_text_element<int*>* at = (new Dynamic_text_element<int*>())->set_properties(&simulation->date.calendar_years, shaderProgram, fontShader, 2000, 1400, "Date: ", simulation->date.postfix);


	graphic_elements.push_back(at);


	Panel* speed_choice_panel = (new Panel())->set_properties(shaderProgram, fontShader, visualization.window_resolution.x / 20 * 18, 1250, 75, 35);
	graphic_elements.push_back(speed_choice_panel);

	for (int i = 0; i < root_menus.size(); i++)
	{
		graphic_elements.push_back(root_menus[i]);
	}

}