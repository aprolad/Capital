#pragma once
#include "Header.h"
class button
{
	public:
};
class quadButton : button
{
	public:
		double x, y;
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
};