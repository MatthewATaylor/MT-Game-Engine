#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace mtge {
	class Window {
	private:
		GLFWwindow *window;

		static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);

	public:
		Window(std::string windowTitle, int screenWidth, int screenHeight, bool resizable);
		void setShouldClose(bool shouldClose);
		bool getShouldClose();
		GLFWwindow *getPtr_GLFW();
		int getWidth();
		int getHeight();
	};
}