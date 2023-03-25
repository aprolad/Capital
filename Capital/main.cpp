#define GLEW_STATIC
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Header.h"
#include "Visualization.h"

#undef main


class sceneComposer
{
private:
	int scenePointer;

public:
	GLuint* shader;
	sceneComposer()
	{
		scenePointer = 0;
	}
	void chooseScene(int scPtr)
	{
		if (scene.size() > scPtr)
			scenePointer = scPtr;

	}
	std::vector<scene*> scene;
	void mouseInvoke(double mx, double my)
	{
		scene[scenePointer]->mouseInvoke(mx, my);

	}
	void draw()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUniform4f(glGetUniformLocation(*shader, "ourColor"), 0.0, 0, 0, 1);
		scene[scenePointer]->draw();
	}
};





int main()
{
	Visualization Visualization;
	//loadConfig(2560, 1440);
	Visualization.window_initialization(Visualization.window);
	base.init();
	Visualization.audio_initalization();



	Visualization.OGL_mainLoop();

	glfwTerminate();
	return 0;
}



