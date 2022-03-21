
#include "../Header.h"
#include "simulation.h"
#include "technologyTab.h"


extern simulation sim;
extern int choosenTab;


	void technologyTab::draw()
	{
		drawBase();

		RenderText(fontShader, "Technology", 680, 980, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		if (active)
		{
			glUseProgram(shaderProgram);
			drawRectangle(-000, -300, 800, -900);

			
		}

	}
