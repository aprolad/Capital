#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//include "Graphics/GUI.h"
#include "Graphics/SceneComposer.h"
void startButton::mouseCallback(double mx, double my)
{
	std::cout << y - size << " " << my << std::endl;
	if (mx > (x - size) && mx < (x + size) && my >(y - size) && my < (y + size))
		scMain.chooseScene(1);
};

void quadButton::draw()
{
	glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
	trans = glm::scale(trans, glm::vec3(size * 5, size * 5, size * 5));
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	poly.draw();
}
void map::display()
{
	glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(0, 0, 0.0f));
	vec = trans * vec;
	//
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	draw();
}