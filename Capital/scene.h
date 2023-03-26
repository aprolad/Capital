#pragma once
#include <vector>
#include "Graphic_element.h"
#include "Visualization.h"
class scene
{
	public:
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
				graphic_elements[i]->init();
		}
};
class mainMenuScene : virtual public scene
{
public:
	void construct_scene()
	{
		graphic_elements.push_back(new Quad_button(shaderProgram, fontShader, 350, 350, "Exit"));
		graphic_elements[0]->action = []() -> void { exit(0); };

		graphic_elements.push_back(new Quad_button(shaderProgram, fontShader, 350, 550, "Start"));
		graphic_elements[1]->action = []() -> void { *choosen_scene = 1; };
	}
	
};


class mainGameScene : virtual public scene
{
public:
	void construct_scene()
	{
		graphic_elements.push_back(new Quad_button(shaderProgram, fontShader, 350, 550, "Return"));
		graphic_elements[0]->action = []() -> void { *choosen_scene = 0; };
	}


};