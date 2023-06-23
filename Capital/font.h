#pragma once
#include <glm/glm.hpp>
#include <map>
#include <string>
struct Character {
	GLuint     TextureID; // ID �������� �����
	glm::ivec2 Size;      // ������� �����
	glm::ivec2 Bearing;   // �������� ������� ����� ����� �����
	GLuint     Advance;   // �������������� �������� �� ������ ���������� �����
};
extern std::map<GLchar, Character> Characters;
void font_init();
void RenderText(GLuint& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
