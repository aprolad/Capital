#pragma once
#include <glew.h>
#include <glfw3.h>
int windowInit(GLFWwindow* &window);
struct resolution 
{
	int x, y;
};
extern resolution screenResolution;