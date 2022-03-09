#pragma once
#include "../Scene.h"
#include "simulation.h"

extern simulation sim;
extern int choosenTab;

class goodsTab
{
public:
	bool active;
	void (*reset)();
	void mouseInvoke(int mx, int my)
	{
		int x = 440;
		int x2 = 640;
		int y = 880;
		int y2 = 1080;

		if (mx > x && mx < x2 && my > y && my < y2)
		{
			bool actTemp = active;
			reset();
			if (actTemp == false)
			active = true;
		}
	}
	void draw()
	{
		using namespace std;
		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(540, 980, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-100, -100, 100, 100);

		


		RenderText(fontShader, "Goods",500, 980, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		if (active)
		{
			glUseProgram(shaderProgram);
			drawRectangle(-000, -300, 600, -900);

			string str = "Wheat price: ";
			str = str + std::to_string(sim.agriculture.wheat.price);
			RenderText(fontShader, str, 500, 300, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}

	}
};