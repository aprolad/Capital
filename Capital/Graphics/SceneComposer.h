#pragma once
#include "GUI.h"
class sceneComposer
{
	public:
		std::vector<quadButton> buttons;
		void draw()
		{
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			for (int i = 0; i < buttons.size(); i++)
				buttons[i].draw();
		}
};