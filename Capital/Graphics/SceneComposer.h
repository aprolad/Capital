#pragma once
#include "Scene.h"

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
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			scene[scenePointer]->draw();
		}
};
extern sceneComposer scMain;
