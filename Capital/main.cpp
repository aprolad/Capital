#define GLEW_STATIC
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Header.h"
#include "Visualization.h"
#include <gdal.h>
#include <gdal_priv.h>
#include <ogr_geometry.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ogrsf_frmts.h>
#undef main



int main()
{
	GDALAllRegister();
	OGRRegisterAll();
	
	Visualization Visualization;
	//loadConfig(2560, 1440);
	Visualization.window_initialization(Visualization.window);
	Visualization.audio_initalization();


	Visualization.OGL_mainLoop();

	glfwTerminate();
	return 0;
}



