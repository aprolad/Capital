#pragma once
#include <vector>
#include "Map.h"
#include "Graphic_element.h"
//#include "Visualization.h"
//
class Scene
{
	public:
		GLFWwindow* window;
		Simulation* simulation;
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
	void construct_scene();
	
};

class SettingsMenuScene : virtual public Scene
{
public:
	void construct_scene();

};

class MainGameScene : virtual public Scene
{
public:
	Map map;
	std::vector<Multiple_choice_panel*> root_menus;
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
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		map.debug += 3;
	}

	void draw()
	{
		if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			map.size *= 0.999;
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			map.size *= 1.001;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			map.y -= 1 / map.size;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			map.y += 1 / map.size;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			map.x += 1 / map.size;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			map.x -= 1 / map.size;
	
		bool any_active = false;
		for (auto i : root_menus)
		{
			any_active += i->active;
		}
		if (!any_active)
			map.draw();
		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);

		for (int i = 0; i < graphic_elements.size(); i++)
			graphic_elements[i]->draw();
		
		
	}


};