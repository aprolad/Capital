//#include "./Interface/tab.h"
//#include "Header.h"
//GLuint shaderProgram, fontShader;
//void tab::drawBase()
//{
//	glUseProgram(shaderProgram);
//	glm::mat4 trans;
//	trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
//	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
//	if (active)
//		glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.2, 0.2, 0.2, 1);
//	drawRectangle(-100, -100, 100, 100);
//	glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);
//}