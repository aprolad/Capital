#include "geographyTab.h"
#include "../Header.h"
#include "../Visualization.h"


extern int choosenTab;



//
//void geographyTab::draw()
//{ 
//	drawBase();
//
//	RenderText(fontShader, "Geography", 1700, 110, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
//
//	if (active)
//	{
//		glUseProgram(shaderProgram);
//		glm::mat4 trans = glm::mat4(1);
//		trans = glm::translate(trans, glm::vec3(0, 0, 0.0f));
//		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
//		drawRectangle(800, 200, 1300, 800);
//
//		string str = "Density ";
//	//	str = str + std::to_string((sim.population.density));
//		RenderText(fontShader, str, 820, 300, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
//
//		str = "Area ";
//	//	str = str + std::to_string(int(sim.geo.sqKilometres));
//		RenderText(fontShader, str, 820, 350, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
//
//	}
//
//}
