#pragma once
#include "../Scene.h"

//#include "../game/simulation.h"
#include "../game/economicsTab.h"
#include "../game/goodsExchangeTab.h"
#include "../game/technologyTab.h"
#include "geographyTab.h"
#include "../demographyTab.h"


extern int choosenSubMenu;
extern int choosenTab;


class textElement
{
	public:
		void draw()
		{
			using namespace std;
			double size = 100;
			glUseProgram(shaderProgram);
			glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
			glm::mat4 trans;
			trans = glm::translate(trans, glm::vec3(200, 200, 0.0f));
			trans = glm::scale(trans, glm::vec3(2, 2, 2));
			GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			string str = "Date: ";
		//	str = str + " Year " + to_string((sim.date - sim.date%365)/365) + " day "+  to_string(sim.date%365) ;
			RenderText(fontShader, str, 1000, 1000, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}
};


class mainStat : virtual public scene
{
	public:
		static demographicsMenu demographics;
		static economicsMenu economics;
		static goodsTab gt;
		static technologyTab tt;
		static geographyTab geoTab;
	mainStat()
	{
		demographics= demographicsMenu(0, 0);
		economics = economicsMenu(220, 0);

		rootMenus.push_back(&demographics);
		rootMenus.push_back(&economics);
		rootMenus.push_back(&gt);
		rootMenus.push_back(&tt);
		rootMenus.push_back(&geoTab);


		gt.reset = resetActive;
		tt.reset = resetActive;
		geoTab.reset = resetActive;
		economics.reset = resetActive;
		demographics.reset = resetActive;



	}
	static std::vector<tab*> rootMenus;
	static textElement date;
	static void mouseInvoke(double mx, double my)
	{
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->mouseInvoke(mx, my);
		for (int i = 0; i < bn.size(); i++)
			bn[i]->mouseCallback(mx, my);

	}
	
	static void draw()
	{

		//for (int i=0;i<15;i++)
		//sim.cycle();


		for (int i = 0; i < bn.size(); i++)
			bn[i]->draw();
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->draw();

		date.draw();
	}
	private:
		static void resetActive()
		{
			for (int i = 0; i < rootMenus.size(); i++)
			{
				rootMenus[i]->active = false;
			}
			gt.active = false;
			tt.active = false;
			geoTab.active = false;
		}
};


