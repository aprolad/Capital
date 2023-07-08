#pragma once
#include "Scene.h"
#include "Visualization.h"

extern Visualization visualization;
extern Simulation simulation;
void MainMenuScene :: construct_scene()
{
	int x_slot = visualization.window_resolution.x / 50;
	Quad_button* t = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot*5, 155, x_slot * 4, 50, "Exit");
	graphic_elements.push_back(t);
	graphic_elements[0]->action = []() -> void { exit(0); };


	t = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot * 5, 480, x_slot * 4, 50, "Start");
	graphic_elements.push_back(t);
	graphic_elements[1]->action = []() -> void { *choosen_scene = 1; };

	t = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot * 5, 260, x_slot * 4, 50, "Settings");
	graphic_elements.push_back(t);
	graphic_elements[2]->action = []() -> void { *choosen_scene = 2; };

	t = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot * 5, 370, x_slot * 4, 50, "Load game");
	graphic_elements.push_back(t);
	graphic_elements[3]->action = []() -> void { *choosen_scene = 1; };

}

void SettingsMenuScene::construct_scene()
{
	Quad_button* t = (new Quad_button())->set_properties(shaderProgram, fontShader, visualization.window_resolution.x / 10, 155, 100, 50, "Return");
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



	Quad_button* return_button = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot * 5, y_slot * 2, x_slot * 3, 50, "Return");
	return_button->action = []() -> void { *choosen_scene = 0; };
	graphic_elements.push_back(return_button);
	
	Quad_button* mobilize_button = (new Quad_button())->set_properties(shaderProgram, fontShader, x_slot * 45, y_slot * 2, x_slot * 3, 50, "Mobilize", 0.9);
	mobilize_button->action = []() -> void { simulation.player.mobilize(); };
	graphic_elements.push_back(mobilize_button);




	root_menus.push_back((new Economics_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 5, y_slot * 45, 150, 50, "Economics"));

	root_menus.push_back((new Society_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 13, y_slot * 45, 150, 50, "Socio"));

	root_menus.push_back((new Technology_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 21, y_slot * 45, 150, 50, "Technology"));

	root_menus.push_back((new Goverment_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 29, y_slot * 45, 150, 50, "Goverment"));

	root_menus.push_back((new Goverment_menu())->set_properties(&root_menus, shaderProgram, fontShader, visualization.x_slot * 29, y_slot * 145, 5150, 50, "Goverment"));


	

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
void MainGameScene::cont_input_check()
{
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			map.size *= 0.999;
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			map.size *= 1.001;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			map.y -= 4 / map.size;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			map.y += 4 / map.size;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			map.x += 4 / map.size;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			map.x -= 4 / map.size;

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (xpos > visualization.window_resolution.x-10)
			map.x -= 10 / map.size;
		if (ypos > visualization.window_resolution.y-10)
			map.y += 10 / map.size;
		if (xpos < 10)
			map.x += 10 / map.size;
		if (ypos < 10)
			map.y -= 10 / map.size;

}
void MainGameScene::draw()
	{
		
		cont_input_check();

		bool any_active = false;
		for (auto i : root_menus)
		{
			any_active += i->active;
		}

		if (!any_active)
			map.draw();

		if (enemy)
			en->draw();



		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);

		for (int i = 0; i < graphic_elements.size(); i++)
			graphic_elements[i]->draw();

		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 1.0, 0.0, 0.0, 1);
		reset_matrix(shaderProgram);
		if (simulation.player.mobilized)
			draw_border(2, 2, visualization.window_resolution.x-2, visualization.window_resolution.y-2, 5);
	}