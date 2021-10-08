#define GLEW_STATIC
#include "Header.h"

GLFWwindow* window;

graphicObject base;
sceneComposer mainMenu;
#undef main

void OGL_mainLoop()
{



	GLuint vertexShader = createVertexShader("Graphics/shaders/vertex.sh");
	GLuint fragmentShader = createFragmentShader("Graphics/shaders/fragment.sh");
	shaderProgram = createShaderProgram(vertexShader, fragmentShader);
	base.init();
	mainMenu.buttons.resize(2);
	mainMenu.buttons[0].poly = base;
	mainMenu.buttons[1].poly = base;
	mainMenu.buttons[1].y += -0.5;
	glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window))
	{
		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLfloat redValue = (cos(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);
		glfwPollEvents();
		mainMenu.draw();

		glfwSwapBuffers(window);
	}
}



int main()
{
	
	windowInit(window);

	glfwSetKeyCallback(window, key_callback);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		std::cout << "!!!";
	}

	// Amount of channels (Max amount of sounds playing at the same time)
	Mix_AllocateChannels(1);
	sample s("audio/1wav.wav", 32000);
	s.play();
	OGL_mainLoop();

	glfwTerminate();
	return 0;
}