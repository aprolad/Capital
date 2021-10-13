#define GLEW_STATIC
#include "Header.h"
#undef main
GLFWwindow* window;


mainMenuScene mainMenu;
sceneComposer scMain;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void OGL_mainLoop()
{
	
	
	scMain.scene.resize(1);
	
	GLuint vertexShader = createVertexShader("Graphics/shaders/vertex.sh");
	GLuint fragmentShader = createFragmentShader("Graphics/shaders/fragment.sh");
	shaderProgram = createShaderProgram(vertexShader, fragmentShader);
	base.init();
	
	mainMenu.bn.push_back(new exitButton(0, -0.5));
	mainMenu.bn.push_back(new startButton(0, 0.0));

	scMain.scene[0] = &mainMenu;
	scMain.scene.push_back(new mapScene());
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
		scMain.draw();

		glfwSwapBuffers(window);
	}
}

int main()
{
	
	windowInit(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		std::cout << "!!!";
	}
	Mix_AllocateChannels(1);
	sample s("audio/1wav.wav", 32000);
	s.play();

	OGL_mainLoop();

	glfwTerminate();
	return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		
		glfwGetCursorPos(window, &xpos, &ypos);
	//	std::cout << ((xpos / 1280) * 2) - 1 << " " << ((ypos / 1024) * 2) - 1 << std::endl;
		scMain.mouseInvoke(((xpos / 1280) * 2) - 1, ((ypos / 1024) * 2) - 1);
	}
}