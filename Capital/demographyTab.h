#pragma once
#include "./Interface/tab.h"
#include "Graphics/chartBuilder.h"
class panel
{
public:
	ageChart pyrChart;

	void draw()
	{
		double temp;
		double stage;
		for (int i = 0; i < 1600; i++)
		{
			temp = 0;
			for (int c = 0; c < 24; c++)
	//			temp += sim.population.agePyramid[i * 25 + c];
			pyrChart.data[i] = temp;
		}
		

		using namespace std;
		double size = 100;

		glUseProgram(shaderProgram);
		glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(300, 350, 0.0f));
		trans = glm::scale(trans, glm::vec3(size / 50, size / 50, size / 50));
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		drawRectangle(-100, -150, 100, 150);

		string str = "Food supply: ";
	//	str = str + std::to_string(int(sim.population.foodSupply));
		RenderText(fontShader, str, 120, 170, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		str = "Population: ";
	//	str = str + std::to_string(int(sim.population.population));
		RenderText(fontShader, str, 120, 200, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		str = "Dependancy rate: ";
	//	str = str + std::to_string((sim.population.dependencyRate));
		RenderText(fontShader, str, 120, 300, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		str = "Deaths: ";
	//	str = str + std::to_string((int(sim.population.fat)));
		RenderText(fontShader, str, 120, 350, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		str = "Births: ";
	//	str = str + std::to_string(int((sim.population.births)));
		RenderText(fontShader, str, 120, 400, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		pyrChart.draw();
	};
};

class demographicsMenu : virtual public tab
{
public:
	panel p;
	demographicsMenu(int x, int y)
	{
		this->x = 100;
		this->y = 980;
	}


	void draw()
	{
		
		drawBase();


		RenderText(fontShader, "Demographics", x - 60, y, 0.5, glm::vec3(1.0, 0.0f, 0.0f));
		if (active)
			p.draw();


	}

};