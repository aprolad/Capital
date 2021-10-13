#pragma once
#include <vector>
#include "Graphics/GUI.h"
class scene
{
	public:
		virtual void draw() {};
		virtual void mouseInvoke(double, double) {};
};
class mainMenuScene : virtual public scene
{
	public:
		std::vector<button*> bn;
		void mouseInvoke(double mx, double my)
		{
			std::cout << "q";
			for (int i = 0; i < bn.size(); i++)
				bn[i]->mouseCallback(mx, my);
		}
		void draw()
		{
			
			for (int i = 0; i < bn.size(); i++)
				bn[i]->draw();
		}
};
class mapScene : virtual public scene
{
	public:
		mapScene()
		{
			a = map();
		}
		map a;
		void draw()
		{
			a.draw();
		}
};