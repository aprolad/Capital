#pragma once
#include "scene.h"

class sceneComposer
{
	private:
		int scenePointer;
	public:
		sceneComposer()
		{
			scenePointer = 0;
		}
		void chooseScene(int scPtr)
		{
			if (scene.size() > scPtr)
			scenePointer = scPtr;
		
		}
		std::vector<scene*> scene;
		void mouseInvoke(double mx, double my)
		{
			scene[scenePointer]->mouseInvoke(mx, my);
		}
		void draw()
		{
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			scene[scenePointer]->draw();
		}
};
extern sceneComposer scMain;
