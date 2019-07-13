#include "Window.h"

namespace mtge {
	void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	//Constructor
	Window::Window(const char *windowTitle, const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {
		window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, 0, 0);
		if (!window) {
			std::cout << "ERROR [FUNCTION: Window]: WINDOW FAILED TO INITIALIZE" << std::endl << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	//Public
	void Window::setResizable(bool resizable) {
		this->resizable = resizable;

		if (resizable) {
			glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
		}
	}
	void Window::setShouldClose(bool shouldClose) {
		glfwSetWindowShouldClose(window, shouldClose);
	}
	bool Window::getResizeable() {
		return resizable;
	}
	bool Window::getShouldClose() {
		return glfwWindowShouldClose(window);
	}
	GLFWwindow *Window::getPtr_GLFW() {
		return window;
	}
}