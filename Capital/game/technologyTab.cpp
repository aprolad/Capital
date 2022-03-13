
#include "../Header.h"
#include "simulation.h"
#include "technologyTab.h"


extern simulation sim;
extern int choosenTab;



	void technologyTab::mouseInvoke(int mx, int my)
	{
		int x = 660;
		int x2 = 860;
		int y = 880;
		int y2 = 1080;

		if (mx > x && mx < x2 && my > y && my < y2)
		{
			bool actTemp = active;
			reset();
			if (actTemp == false)
				active = true;
		}
	}
	void technologyTab::draw()
	{
		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(760, 980, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-100, -100, 100, 100);

		RenderText(fontShader, "Technology", 680, 980, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

		if (active)
		{
			glUseProgram(shaderProgram);
			drawRectangle(-000, -300, 800, -900);

			
		}

	}
