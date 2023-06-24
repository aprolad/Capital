#define GLEW_STATIC
#include <ft2build.h>
#include FT_FREETYPE_H
#include "./Source/Header.h"
#include "Source/Visualization/Visualization.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "Source/Utility/stb_image_resize.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Source/Utility/stb_image.h"
#undef main
Visualization visualization = Visualization();
Simulation simulation = Simulation();

int main()
{


	//loadConfig(2560, 1440);

	visualization.start();

	glfwTerminate();
	return 0;
}



