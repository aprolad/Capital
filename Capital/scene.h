#pragma once
#include <vector>
#include "Graphics/GUI.h"

class scene
{
	public:
		std::vector<button*> bn;
		virtual void draw() {};
		virtual void mouseInvoke(double mx, double my)
		{
			for (int i = 0; i < bn.size(); i++)
				bn[i]->mouseCallback(mx, my);
		}
};
class mainMenuScene : virtual public scene
{
	public:
		
		void mouseInvoke(double mx, double my)
		{	
			for (int i = 0; i < bn.size(); i++)
				bn[i]->mouseCallback(mx, my);
		}
		void draw()
		{	
			for (int i = 0; i < bn.size(); i++)
				bn[i]->draw();
		}
};


