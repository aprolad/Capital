#define GLEW_STATIC
#include "Header.h"


GLFWwindow* window;

graphicObject base;
void OGL_mainLoop()
{
	GLuint vertexShader = createVertexShader("Graphics/shaders/vertex.sh");
	GLuint fragmentShader = createFragmentShader("Graphics/shaders/fragment.sh");
	GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);
	
	base.init();


	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(base.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
}
int main()
{
	
	windowInit(window);

	glfwSetKeyCallback(window, key_callback);

	OGL_mainLoop();

	glfwTerminate();
	return 0;
}