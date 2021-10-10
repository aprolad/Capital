#pragma once
#include "GUI.h"
#include "scene.h"
class sceneComposer
{
	public:
		std::vector<scene> scene;
		void draw()
		{
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			scene[0].draw();
		}
};