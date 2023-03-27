#pragma once

#include "Header.h"

//#include "Interface/mainStatistic.h"
#include "Graphics/CAP_shaderAux.h"
#include "audio.h"

#include "Scene.h"
class Visualization
{
public:
Visualization ()
{

}
	static simulation simulation;
	GLuint shaderProgram;
	GLuint fontShader;
	static mainMenuScene m;
	static mainGameScene mm;
	static int choosenScene;
	GLFWwindow* window;
	static std::vector<scene*> scene;
	int window_initialization(GLFWwindow*& window)
	{

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		window = glfwCreateWindow(2560, 1440, "Capital", nullptr, nullptr);
		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			return -1;
		}

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		//glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 2560, 1920, GLFW_DONT_CARE);
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
	}
	int audio_initalization()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
			std::cout << "!!!";
		}
		Mix_AllocateChannels(1);
		//sample s("audio/1wav.wav", 32000);
		//s.play();
		return 0;
	}
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			scene[choosenScene]->mouseInvoke(xpos, 1440 - ypos);
		}
	}
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

			if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
				simulation.pause();

	}
	void construct_game()
	{
		m.shaderProgram = shaderProgram;
		m.choosen_scene = &choosenScene;
		m.fontShader = fontShader;
		m.simulation = &simulation;
		m.initialize();
		
		scene.push_back(&m);

		mm.shaderProgram = shaderProgram;
		mm.choosen_scene = &choosenScene;
		mm.fontShader = fontShader;
		mm.simulation = &simulation;
		mm.initialize();
		scene.push_back(&mm);
	}
	void OGL_mainLoop()
	{
		GLuint vertexShader = createVertexShader("Graphics/shaders/vertex.sh");
		GLuint fragmentShader = createFragmentShader("Graphics/shaders/fragment.sh");
		shaderProgram = createShaderProgram(vertexShader, fragmentShader);

		vertexShader = createVertexShader("Graphics/shaders/vertexFont.sh");
		fragmentShader = createFragmentShader("Graphics/shaders/fragmentFont.sh");
		fontShader = createShaderProgram(vertexShader, fragmentShader);

		fontInit();

	
		construct_game();


		glUseProgram(shaderProgram);
		while (!glfwWindowShouldClose(window))
		{
			glm::mat4 projection = glm::ortho(0.0f, float(2560), 0.0f, float(1440));
			glUseProgram(shaderProgram);
			GLuint transformLoc = glGetUniformLocation(shaderProgram, "projection");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));

			glfwPollEvents();

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0, 0, 1);

			simulation.cycle();
			scene[choosenScene]->draw();

		


			glUseProgram(fontShader);
			transformLoc = glGetUniformLocation(fontShader, "projection");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));

			glfwSwapBuffers(window);
		}
	}
	void process()
	{

	}
};