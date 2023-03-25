#pragma once
#include "../Scene.h"
#include "simulation.h"


extern int choosenTab;

class goodsTab : virtual public tab
{
public:

	goodsTab()
	{
		x = 540;
		y = 980;
	}
	void draw()
	{
		drawBase();

		
		RenderText(fontShader, "Goods",450, 980, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		if (active)
		{
			glUseProgram(shaderProgram);
			drawRectangle(-000, -300, 600, -900);

			string str = "Wheat price: ";
			str = str + std::to_string(0);// sim.agriculture.wheat.price);
			RenderText(fontShader, str, 700, 300, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}

	}
};