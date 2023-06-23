#pragma once
#include <glm/glm.hpp>
#include <map>
#include <string>
struct Character {
	GLuint     TextureID; // ID текстуры глифа
	glm::ivec2 Size;      // Размеры глифа
	glm::ivec2 Bearing;   // Смещение верхней левой точки глифа
	GLuint     Advance;   // Горизонтальное смещение до начала следующего глифа
};
extern std::map<GLchar, Character> Characters;
void font_init();
void RenderText(GLuint& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
