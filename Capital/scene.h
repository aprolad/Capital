#pragma once
#include <vector>
#include "Graphics/GUI.h"
#include "game/playground.h"
class scene
{
	public:
		std::vector<button*> bn;
		virtual void draw() {};
		void mouseInvoke(double mx, double my)
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
class mapScene : virtual public scene
{
	public:
		mapScene(playground pl)
		{
			this->pl = pl;
			a = map();
			a.init();
		}
		map a;
		playground pl;
		void draw()
		{
			for (int i = 0; i < bn.size(); i++)
				bn[i]->draw();
			pl.draw();
		}
};