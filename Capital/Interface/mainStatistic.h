#pragma once
#include "../Scene.h"

#include "game/simulation.h"
#include "game/economicsTab.h"
#include "game/goodsExchangeTab.h"
#include "game/technologyTab.h"
#include "geographyTab.h"
#include "../demographyTab.h"
simulation sim;

int choosenSubMenu;
int choosenTab;



void resetActive();



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
			str = str + " Year " + to_string((sim.date - sim.date%365)/365) + " day "+  to_string(sim.date%365) ;
			RenderText(fontShader, str, 1000, 1000, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		}
};

demographicsMenu demographics(0, 0);
economicsMenu economics(220, 0);
goodsTab gt;
technologyTab tt;
geographyTab geoTab;
class mainStat : virtual public scene
{
	public:

	mainStat()
	{

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
	std::vector<tab*> rootMenus;
	textElement date;
	void mouseInvoke(double mx, double my)
	{
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->mouseInvoke(mx, my);
		for (int i = 0; i < bn.size(); i++)
			bn[i]->mouseCallback(mx, my);

	}
	
	void draw()
	{

		for (int i=0;i<15;i++)
		sim.cycle();


		for (int i = 0; i < bn.size(); i++)
			bn[i]->draw();
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->draw();

		date.draw();
	}
	private:

};



mainStat mainScene;

void resetActive()
{
	for (int i = 0; i < mainScene.rootMenus.size(); i++)
	{
		mainScene.rootMenus[i]->active = false;
	}
	gt.active = false;
	tt.active = false;
	geoTab.active = false;
}