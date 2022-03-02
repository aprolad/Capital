#pragma once
extern int choosenTab;
class goodsTab
{
public:
	bool active;
	void mouseInvoke(int mx, int my)
	{
		int size = 100;
		int x = 20;
		int x2 = 220;
		int y = 750;
		int y2 = 850;

		if (mx > x && mx < x2 && my > y && my < y2)
		{
			active = !active;
			choosenTab = 3;
		}
	}
	void draw()
	{
		glUseProgram(shaderProgram);
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(540, 980, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		drawRectangle(-100, -100, 100, 100);

		RenderText(fontShader, "Goods",500, 980, 0.5, glm::vec3(1.0, 0.0f, 0.0f));

	}
};