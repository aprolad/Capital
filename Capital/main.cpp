#define GLEW_STATIC
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Header.h"
#include "Visualization.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "misc/stb_image_resize.h"
#define STB_IMAGE_IMPLEMENTATION
#include "misc/stb_image.h"
#undef main

Visualization visualization = Visualization();
Simulation simulation = Simulation();

int main()
{


	//loadConfig(2560, 1440);
	//visualization.window_initialization(visualization.window);

	visualization.audio_initalization();


	visualization.OGL_mainLoop();

	glfwTerminate();
	return 0;
}



