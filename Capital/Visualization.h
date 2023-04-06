#pragma once

#include "Header.h"
#include "Graphics/CAP_shaderAux.h"
#include "audio.h"
#include "Scene.h"
class Visualization
{
public:
	Visualization(){}

	static simulation simulation;
	GLuint shaderProgram;
	GLuint fontShader;
	static MainMenuScene m;
	static MainGameScene mm;
	static SettingsMenuScene a;
	static int choosenScene;
	GLFWwindow* window;
	static std::vector<Scene*> scene;
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
		glfwSetWindowMonitor(window, nullptr, 0, 0, 2560, 1440, GLFW_DONT_CARE);
		//glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 2560, 1440, GLFW_DONT_CARE);
		glfwSwapInterval(1);
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
	}
	int audio_initalization()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
			std::cout << "Audio library error";
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
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			glfwGetCursorPos(window, &xpos, &ypos);
			scene[choosenScene]->mouseInvoke(xpos, height - ypos);
		}
	}
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_F && action == GLFW_PRESS)
		{
			fullscreen = !fullscreen;
			if (fullscreen)
			{
				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 2560, 1440, GLFW_DONT_CARE);
			}
			else
			{
				glfwSetWindowMonitor(window, nullptr, 0, 0, 2560, 1440, GLFW_DONT_CARE);
			}
		}
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		

		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			simulation.pause();
		//if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
			scene[1]->keyboard_callback(window, key, scancode, action, mode);

	}
	void construct_game()
	{


		m.simulation = &simulation;
		m.initialize(shaderProgram, fontShader, &choosenScene);
		scene.push_back(&m);


		mm.simulation = &simulation;
		mm.initialize(shaderProgram, fontShader, &choosenScene);
		mm.window = window;
		scene.push_back(&mm);

		
		a.simulation = &simulation;
		a.initialize(shaderProgram, fontShader, &choosenScene);
		scene.push_back(&a);



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
		glfwSetTime(0.0);
		double avgFps = 0;
		double totalTime = 0.0;
		int frameCount = 0;
		glUseProgram(shaderProgram);
	
		while (!glfwWindowShouldClose(window))
		{
			double elapsed = glfwGetTime();
			glfwSetTime(0.0);

			double fps = 1.0 / elapsed;


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
			RenderText(fontShader, "FPS: " + std::to_string(avgFps), 20, 50, 0.3, glm::vec3(1.0, 0.0f, 0.0f));
		
			glUseProgram(fontShader);
			transformLoc = glGetUniformLocation(fontShader, "projection");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));

			glfwSwapBuffers(window);
			frameCount++;
			totalTime += elapsed;

			
			// Calculate the average frame rate every 100 frames
			if (frameCount % 100 == 0)
			{
				avgFps = 100.0 / totalTime;
				frameCount = 0;
				totalTime = 0.0;
			}
		}
	}
	void process()
	{

	}
	private:
		static bool fullscreen;
};
