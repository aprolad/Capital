#pragma once
#include <glew.h>
#include <glfw3.h>
GLuint createVertexShader(const char* path);
GLuint createFragmentShader(const char* path);
GLuint createShaderProgram(GLuint vertex, GLuint fragment);