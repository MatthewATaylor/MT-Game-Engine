#include "Window.h"

namespace mtge {
	//Constructor
	Window::Window(std::string windowTitle, int screenWidth, int screenHeight, bool resizable) {
		if (!resizable) {
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		}

		window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), 0, 0);
		if (!window) {
			std::cout << "ERROR [FUNCTION: Window]: WINDOW FAILED TO INITIALIZE" << std::endl << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);

		if (resizable) {
			glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		glViewport(0, 0, screenWidth, screenHeight);
		glScissor(0, 0, screenWidth, screenHeight);
	}

	//Private
	void Window::frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	//Public
	void Window::setShouldClose(bool shouldClose) {
		glfwSetWindowShouldClose(window, shouldClose);
	}
	bool Window::getShouldClose() {
		return glfwWindowShouldClose(window);
	}
	GLFWwindow *Window::getPtr_GLFW() {
		return window;
	}
	int Window::getWidth() {
		int viewportData[4];
		glGetIntegerv(GL_VIEWPORT, viewportData);
		return viewportData[2];
	}
	int Window::getHeight() {
		int viewportData[4];
		glGetIntegerv(GL_VIEWPORT, viewportData);
		return viewportData[3];
	}
}