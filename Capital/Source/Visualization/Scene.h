#pragma once
#include <vector>
#include "Map.h"
#include "Graphic_elements.h"
//#include "Visualization.h"
extern Simulation simulation;
//extern Visualization visualization;
//
//
class Scene
{
	public:
	
		bool enemy;
		GLFWwindow* window;
		//Simulation* simulation;
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
		virtual void mouseScrollInvoke(double mx, double my)
		{
		}
		virtual void mouse_move_invoke(double mx, double my)
		{
			for (int i = 0; i < graphic_elements.size(); i++)
				graphic_elements[i]->mouse_move_callback(mx, my);
		}
		virtual void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
		{};
		virtual void construct_scene() {};
		virtual void initialize(GLuint shaderProg, GLuint fontSh, int* chSC)
		{
			shaderProgram = shaderProg;
			fontShader = fontSh;
			choosen_scene = chSC;

			construct_scene();
			for (int i = 0; i < graphic_elements.size(); i++)
			{
				graphic_elements[i]->init();
			}
		}
};
class MainMenuScene : virtual public Scene
{
public:
	MainMenuScene(GLuint shaderProg, GLuint fontSh, int* chSC)
	{
		shaderProgram = shaderProg;
		fontShader = fontSh;
		choosen_scene = chSC;

		construct_scene();
		for (int i = 0; i < graphic_elements.size(); i++)
		{
			graphic_elements[i]->init();
		}
	}
	void construct_scene();
	
};

class SettingsMenuScene : virtual public Scene
{
public:
	SettingsMenuScene(GLuint shaderProg, GLuint fontSh, int* chSC)
	{
		shaderProgram = shaderProg;
		fontShader = fontSh;
		choosen_scene = chSC;

		construct_scene();
		for (int i = 0; i < graphic_elements.size(); i++)
		{
			graphic_elements[i]->init();
		}
	}
	void construct_scene();

};

class MainGameScene : virtual public Scene
{
public:
	MainGameScene(GLuint shaderProg, GLuint fontSh, int* chSC, GLFWwindow* _window)
	{
		window = _window;
		shaderProgram = shaderProg;
		fontShader = fontSh;
		choosen_scene = chSC;

		construct_scene();
		for (int i = 0; i < graphic_elements.size(); i++)
		{
			graphic_elements[i]->init();
		}
	}
	Map map;
	std::vector<Multiple_choice_panel*> root_menus;
	Information_panel* en;
	void construct_scene();
	void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
		map.size *= 0.9;
	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
		map.size *= 1.1;
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		map.y -= 25 / map.size;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		map.y += 25 / map.size;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		map.x += 25 / map.size;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		map.x -= 25 / map.size;

	}

	void draw();

	void mouseInvoke(double mx, double my)
	{
		map.mouse_callback(mx, my);
		for (int i = 0; i < graphic_elements.size(); i++)
			graphic_elements[i]->mouseCallback(mx, my);
	}
	void mouseScrollInvoke(double mx, double my)
	{
		    if (my > 0) {
				map.size*= 1 + 0.1 * abs(my);  // Scroll up
			} else if (my < 0) {
				map.size/= 1 + 0.1 * abs(my);  // Scroll down
			}
	}
};