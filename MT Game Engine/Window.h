#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace mtge {
	void frameBufferSizeCallback(GLFWwindow *window, int width, int height);

	class Window {
	private:
		GLFWwindow *window;
		bool resizable = false;

	public:
		Window(const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
		void setResizable(bool resizable);
		void setShouldClose(bool shouldClose);
		bool getResizeable();
		bool getShouldClose();
		GLFWwindow *getPtr_GLFW();
	};
}