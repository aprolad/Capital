#pragma once
#include <glm/glm.hpp>
#include <map>
struct Character {
	GLuint     TextureID; // ID �������� �����
	glm::ivec2 Size;      // ������� �����
	glm::ivec2 Bearing;   // �������� ������� ����� ����� �����
	GLuint     Advance;   // �������������� �������� �� ������ ���������� �����
};
extern std::map<GLchar, Character> Characters;
void fontInit();
void RenderText(GLuint& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
struct title
{

};