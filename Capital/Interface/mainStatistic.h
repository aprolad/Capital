#pragma once
#include "../Scene.h"




class panel
{
	public:
		virtual void draw()
		{

		};
};

panel demo;



class rootMenu
{
public:
	int resx; int resy;
	rootMenu()
	{
		resx = 1280;
		resy = 1024;
	}
	virtual void draw(int resx, int resy) {};
	virtual void mouseCallback(int mx, int my) {};
};


class demographicsMenu : virtual public rootMenu
{
public:
	double x, y;
	demographicsMenu(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void mouseCallback(int mx, int my) {
		int size = 100;
		my = resy -my;
		if (mx > (x) && mx < (x + 2 * size) && my >(y - 0.5 * size) && my < (y + 1.5 * size))
			std::cout << "yes";
	}
	
	void draw(int resx, int resy)
	{
		double size = 100;
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(size + x, resy - size / 2 + y, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		base.draw();

		RenderText(fontShader, "Demographics", x + size - size * 0.9, resy - size / 2 - y, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
	}

};

class economicsMenu : virtual public rootMenu
{
public:
	double x, y;
	economicsMenu(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void mouseCallback(int mx, int my) {
		int size = 100;
		my = resy - my;
		if (mx > (x) && mx < (x + 2 * size) && my >(y - 0.5 * size) && my < (y + 1.5 * size))
			std::cout << "yes";
	}
	
	void draw(int resx, int resy)
	{
		double size = 100;
		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(size + x, resy - size / 2 - y, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		base.draw();

		RenderText(fontShader, "Economics", x + size - size * 0.9, resy - size / 2 - y, size / 200, glm::vec3(1.0, 0.0f, 0.0f));
	}

};





demographicsMenu demographics(0, 0);
economicsMenu economics(220, 0);



















class mainStat : virtual public scene
{
	public:
		int resolutionX, resolutionY;
	mainStat(int resx, int resy)
	{
		resolutionX = resx;
		resolutionY = resy;
		rootMenus.push_back(&demographics);
		rootMenus.push_back(&economics);
	}
	std::vector<rootMenu*> rootMenus;

	void mouseInvoke(double mx, double my)
	{
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->mouseCallback(mx, my);
		for (int i = 0; i < bn.size(); i++)
			bn[i]->mouseCallback(mx, my);
		
	}

	void draw()
	{
		for (int i = 0; i < bn.size(); i++)
			bn[i]->draw();
		for (int i = 0; i < rootMenus.size(); i++)
			rootMenus[i]->draw(1280, 1024);
	}
	private:

};



mainStat mainScene(1280, 1024);

