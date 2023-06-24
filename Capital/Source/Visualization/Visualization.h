#pragma once

#include "Shader_loader.h"
#include "../Header.h"
#include "Audio.h"
#include "Scene.h"
#include "../Utility/stb_image.h"
#include "../Utility/stb_image_resize.h"

extern Simulation simulation;
class Visualization
{
public:
	Visualization()
	{

		std::cout << "Visualization construction started" << std::endl;
		glewExperimental = GL_TRUE; 
		glfwInit();
		window_resolution.x = 1920;
		window_resolution.y = 1080;
		x_slot = window_resolution.x / 50;
		y_slot = window_resolution.y / 50;
		window_initialization(this->window);
		audio_initalization();
		simulation.world.init();
	}
	int x_slot;
	int y_slot;
	static glm::vec2 window_resolution;
	GLuint shaderProgram;
	GLuint fontShader;

	static int choosenScene;
	GLFWwindow* window;
	static std::vector<Scene*> scene;
	int window_initialization(GLFWwindow*& window)
	{

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		window = glfwCreateWindow(window_resolution.x, window_resolution.y, "Capital", nullptr, nullptr);
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
		else
		{
			std::cout << "GLEW OK" << std::endl;
		}

		int widtht, heightt;
		glfwGetFramebufferSize(window, &widtht, &heightt);

		glViewport(0, 0, widtht, heightt);
		glfwSetWindowMonitor(window, nullptr, 0, 0, window_resolution.x, window_resolution.y, GLFW_DONT_CARE);
		//glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 2560, 1440, GLFW_DONT_CARE);
		glfwSwapInterval(1);

		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, mouse_move_callback);
		glfwSetScrollCallback(window, scrollCallback);
		int icon_size = 256;

		// Load the PNG image using stb_image
		int width, height, channels;
		unsigned char* icon_pixels = stbi_load("icon.png", &width, &height, &channels, STBI_rgb_alpha);

		// Create a GLFWimage struct and set its width, height, and pixel data
		GLFWimage icon;
		icon.width = width;
		icon.height = height;
		icon.pixels = icon_pixels;

		// Set the image as the GLFW window icon
		glfwSetWindowIcon(window, 1, &icon);

		// Free the allocated memory for the image pixels
		stbi_image_free(icon_pixels);

		std::cout << "Visualization constructed" << std::endl;
	}
	int audio_initalization()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
			std::cout << "Audio library error";
		}
		Mix_AllocateChannels(1);
		//sample s("Resoruces/Audio/1wav.wav", 32000);
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

	static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
	{
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			scene[choosenScene]->mouse_move_invoke(xpos, height - ypos);
	}
	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	scene[choosenScene]->mouseScrollInvoke(xOffset, yOffset);

}
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_F && action == GLFW_PRESS)
		{
			fullscreen = !fullscreen;
			if (fullscreen)
			{
				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, window_resolution.x, window_resolution.y, GLFW_DONT_CARE);
				glfwSwapInterval(1);
			}
			else
			{
				glfwSetWindowMonitor(window, nullptr, 0, 0, window_resolution.x, window_resolution.y, GLFW_DONT_CARE);
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

		scene.push_back(new MainMenuScene(shaderProgram, fontShader, &choosenScene));

		scene.push_back(new MainGameScene(shaderProgram, fontShader, &choosenScene, window));
		
		scene.push_back(new SettingsMenuScene(shaderProgram, fontShader, &choosenScene));

	}
	void create_shaders()
	{
		GLuint vertexShader = createVertexShader("Resources/Shaders/vertex.sh");
		GLuint fragmentShader = createFragmentShader("Resources/Shaders/fragment.sh");
		shaderProgram = createShaderProgram(vertexShader, fragmentShader);

		vertexShader = createVertexShader("Resources/shaders/vertexFont.sh");
		fragmentShader = createFragmentShader("Resources/shaders/fragmentFont.sh");
		fontShader = createShaderProgram(vertexShader, fragmentShader);
	}
	void start()
	{
		create_shaders();

		font_init();

	
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

			int width, height;
			glfwGetFramebufferSize(window, &width, &height);

			glm::mat4 projection = glm::ortho(0.0f, float(window_resolution.x), 0.0f, float(height));
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
