#pragma once
#include <vector>
#include "Graphic_element.h"
#include "Visualization.h"
class scene
{
	public:
		simulation* simulation;
		static int* choosen_scene;
		GLuint shaderProgram, fontShader;
		std::vector<Graphic_element*> graphic_elements;
		virtual void draw()
		{

			for (int i = 0; i < graphic_elements.size(); i++)
				graphic_elements[i]->draw();
		}
		virtual void mouseInvoke(double mx, double my)
		{
			for (int i = 0; i < graphic_elements.size(); i++)
				graphic_elements[i]->mouseCallback(mx, my);
		}
		virtual void construct_scene() {};
		virtual void initialize()
		{
			construct_scene();
			for (int i = 0; i < graphic_elements.size(); i++)
			{
				
				graphic_elements[i]->simulation = simulation;
				graphic_elements[i]->init();

			}
		}
};
class mainMenuScene : virtual public scene
{
public:
	void construct_scene()
	{
		Quad_button* t = (new Quad_button())->set_properties(shaderProgram, fontShader, 2250, 150, 100, 50, "Exit");
		graphic_elements.push_back(t);
		graphic_elements[0]->action = []() -> void { exit(0); };



		t = (new Quad_button())->set_properties(shaderProgram, fontShader, 2250, 400, 100, 50, "Start");
		graphic_elements.push_back(t);
		graphic_elements[1]->action = []() -> void { *choosen_scene = 1; };

	}
	
};


class mainGameScene : virtual public scene
{
public:

	std::vector<Top_menu*> root_menus;
	void construct_scene()
	{
		
		Quad_button* t = (new Quad_button())->set_properties(shaderProgram, fontShader, 2250, 400, 100, 50, "Return");
		graphic_elements.push_back(t);
		graphic_elements[0]->action = []() -> void { *choosen_scene = 0; };

		
		root_menus.push_back((new Economics_menu())->set_properties(&root_menus, shaderProgram, fontShader, 200, 1270, 150, 50, "Economics"));

		root_menus.push_back((new Demographics_menu())->set_properties(&root_menus, shaderProgram, fontShader, 600, 1270, 150, 50, "Demographics"));

		Dynamic_text_element<int*>* at = (new Dynamic_text_element<int*>())->set_properties(&simulation->date, shaderProgram, fontShader, 2000, 1400, "Date: ");
		t->init();
		graphic_elements.push_back(at);

		for (int i = 0; i< root_menus.size(); i++)
		{
			graphic_elements.push_back(root_menus[i]);
		}
		
	}


};