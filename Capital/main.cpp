#define GLEW_STATIC
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Header.h"

#undef main

GLFWwindow* window;
mainMenuScene mainMenu;
sceneComposer scMain;
resolution screenResolution;
playground pl;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void config()
{
	pl.generate();

	scMain.scene.resize(1);
	mainMenu.bn.push_back(new exitButton(500, 300, 100));
	mainMenu.bn.push_back(new startButton(500, 700, 150));
	scMain.scene[0] = &mainMenu;
	scMain.scene.push_back(new mapScene(pl));
	returnButton *b =new returnButton(screenResolution.x - 100, screenResolution.y - 100, 100);
	b -> func = exitFromMainMenu;
	scMain.scene[1] -> bn.push_back(b);


	
}

void OGL_mainLoop()
{
	
	GLuint vertexShader = createVertexShader("Graphics/shaders/vertex.sh");
	GLuint fragmentShader = createFragmentShader("Graphics/shaders/fragment.sh");
	shaderProgram = createShaderProgram(vertexShader, fragmentShader);

	vertexShader = createVertexShader("Graphics/shaders/vertexFont.sh");
	fragmentShader = createFragmentShader("Graphics/shaders/fragmentFont.sh");
	fontShader = createShaderProgram(vertexShader, fragmentShader);
	
		
	config();

	fontInit();
	

	glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 projection = glm::ortho(0.0f, float(screenResolution.x), 0.0f, float(screenResolution.y));
		glUseProgram(shaderProgram);
		GLuint transformLoc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glfwPollEvents();

		scMain.draw();
		glUseProgram(fontShader);
		
		transformLoc = glGetUniformLocation(fontShader, "projection");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		glfwSwapBuffers(window);
	}
}

int main()
{
	loadConfig(screenResolution.x, screenResolution.y);
	windowInit(window);
	base.init();
	baseGT.init();
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
		scMain.mouseInvoke(xpos, screenResolution.y - ypos);
	}
}