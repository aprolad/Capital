#include "geographyTab.h"
#include "../Header.h"
#include "../game/simulation.h"


extern simulation sim;
extern int choosenTab;



void geographyTab::mouseInvoke(int mx, int my)
{
	int x = 1660;
	int x2 = 1860;
	int y = 0;
	int y2 = 200;

	if (mx > x && mx < x2 && my > y && my < y2)
	{
		bool actTemp = active;
		reset();
		if (actTemp == false)
			active = true;
	}
}
void geographyTab::draw()
{
	glUseProgram(shaderProgram);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1760, 100, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
	drawRectangle(-100, -100, 100, 100);

	RenderText(fontShader, "Geography", 1700, 110, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

	if (active)
	{
		glUseProgram(shaderProgram);
		trans = glm::mat4(1);
		trans = glm::translate(trans, glm::vec3(0, 0, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(800, 200, 1300, 800);

		string str = "Density ";
		str = str + std::to_string((sim.population.density));
		RenderText(fontShader, str, 820, 300, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

	}

}
