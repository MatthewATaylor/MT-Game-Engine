#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace mtge {
	class Window {
	private:
		GLFWwindow *window;

		static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);

	public:
		Window(const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, bool resizable);
		void setShouldClose(bool shouldClose);
		bool getShouldClose();
		GLFWwindow *getPtr_GLFW();
	};
}