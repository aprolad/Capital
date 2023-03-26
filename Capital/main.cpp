#define GLEW_STATIC
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Header.h"
#include "Visualization.h"

#undef main



int main()
{
	Visualization Visualization;
	//loadConfig(2560, 1440);
	Visualization.window_initialization(Visualization.window);
	Visualization.audio_initalization();


	Visualization.OGL_mainLoop();

	glfwTerminate();
	return 0;
}



