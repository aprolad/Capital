#pragma once
#include "Scene.h"

class sceneComposer
{
	private:
		int scenePointer;
		
	public:
		GLuint* shader;
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
			glUniform4f(glGetUniformLocation(*shader, "ourColor"), 0.0,0,0,1);
			scene[scenePointer]->draw();
		}
};
extern sceneComposer scMain;
 