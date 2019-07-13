#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace mtge {
	class Window {
	private:
		GLFWwindow *window;

	public:
		Window(const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, bool resizable);
		static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
		void setShouldClose(bool shouldClose);
		bool getShouldClose();
		GLFWwindow *getPtr_GLFW();
	};
}