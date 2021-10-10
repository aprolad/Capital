#pragma once
#include "Header.h"
class button
{
	public:
		virtual void draw() {};
		virtual void mouseCallback(double, double) {};
};
class quadButton :virtual public button
{
	public:
		quadButton()
		{
			this->x = 0;
			this->y = 0;
			this->size = 0.2;
			poly = base;
		}
		quadButton(double x, double y)
		{
			this->x = x;
			this->y = y;
			this->size = 0.2;
			poly = base;
		}
		double x, y;
		double size;
		graphicObject poly;
		void draw()
		{
			glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
			glm::mat4 trans;
			trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
			vec = trans * vec;
			GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			poly.draw();
		}
		void mouseCallback(double mx, double my)
		{
		//	if (mx > (x - 0.2) && mx < (x + 0.2) && my >(y - 0.2) && my < (y + 0.2))
		//		exit(1);
		}
};
class exitButton : public quadButton
{
	public:
		exitButton(double x, double y)
		{
			this->x = x;
			this->y = y;
			this->size = 0.2;
			poly = base;
		}
		void mouseCallback(double mx, double my)
		{
			if (mx > (x - size) && mx < (x + size) && my > (1 + y - size) && my < (1 + y + size))
				exit(1);
		}

};
